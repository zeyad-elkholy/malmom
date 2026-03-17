# Mini POSIX Shell — Implementation Guide

> **Why this document exists:**  
> Section G of [`OPEN_SOURCE_RECOMMENDATIONS.md`](OPEN_SOURCE_RECOMMENDATIONS.md) ranked a mini POSIX shell as the #2 best next CV project (score 18/20).  
> This guide answers **"how can the code be good?"** — covering architecture, data structures, concrete C++ code stubs, testing strategy, code-quality checklist, and common pitfalls.

---

## Table of Contents

1. [Project Goals & Scope](#1-project-goals--scope)
2. [Directory Layout](#2-directory-layout)
3. [Architecture Overview](#3-architecture-overview)
4. [Data Structures](#4-data-structures)
5. [Stage 1 — Lexer](#5-stage-1--lexer)
6. [Stage 2 — Parser](#6-stage-2--parser)
7. [Stage 3 — Executor](#7-stage-3--executor)
8. [Stage 4 — Built-in Commands](#8-stage-4--built-in-commands)
9. [Stage 5 — Signal Handling](#9-stage-5--signal-handling)
10. [Stage 6 — Job Control](#10-stage-6--job-control)
11. [Error Handling Patterns](#11-error-handling-patterns)
12. [Testing Strategy](#12-testing-strategy)
13. [Code-Quality Checklist](#13-code-quality-checklist)
14. [Common Pitfalls](#14-common-pitfalls)
15. [Suggested Commit Milestones](#15-suggested-commit-milestones)
16. [Key References](#16-key-references)

---

## 1. Project Goals & Scope

### MVP feature set (≈ 3 weeks)

| Feature | System calls used | Demonstrates |
|---------|------------------|-------------|
| Run external commands | `fork`, `execvp`, `waitpid` | Process lifecycle |
| Pipelines (`cmd1 \| cmd2 \| cmd3`) | `pipe`, `dup2`, `close` | IPC, file descriptors |
| I/O redirection (`<`, `>`, `>>`) | `open`, `dup2`, `close` | File descriptor plumbing |
| Builtins: `cd`, `pwd`, `exit`, `export`, `echo`, `unset` | `chdir`, `getcwd`, `setenv` | POSIX env API |
| `$VAR` and `~` expansion | `getenv`, `wordexp` | String processing |

### Stretch features (week 4–5)

| Feature | Adds |
|---------|------|
| Job control (`&`, `fg`, `bg`, `jobs`) | `SIGCHLD`, `SIGTSTP`, `tcsetpgrp` |
| Command history (↑/↓) | `readline` or manual ring-buffer |
| Here-documents (`<<`) | Temp-file trick or `pipe` |
| `&&`, `\|\|`, `;` sequencing | Parser precedence |

---

## 2. Directory Layout

```
zsh/                          ← repo root (name it whatever you like)
├── CMakeLists.txt
├── README.md
├── include/
│   ├── lexer.h
│   ├── parser.h
│   ├── executor.h
│   ├── builtins.h
│   ├── jobs.h
│   └── shell.h
├── src/
│   ├── main.cpp
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── executor.cpp
│   ├── builtins.cpp
│   └── jobs.cpp
└── tests/
    ├── run_tests.sh          ← master test runner
    ├── t01_basic_commands.sh
    ├── t02_pipes.sh
    ├── t03_redirections.sh
    ├── t04_builtins.sh
    └── t05_job_control.sh
```

**Why this layout is good:**  
- One class per `.h`/`.cpp` pair → easy to navigate, easy to test in isolation  
- `tests/` at the top level signals professionalism to any GitHub visitor  
- `CMakeLists.txt` lets reviewers build with a single `cmake .. && make`

---

## 3. Architecture Overview

```
  ┌─────────────────────────────────────────────────────┐
  │                     Shell REPL                       │
  │  read_line() → Lexer → Parser → Executor → repeat    │
  └─────────────────────────────────────────────────────┘

         Input string
              │
              ▼
    ┌─────────────────┐
    │     Lexer        │   "ls -la | grep foo > out.txt"
    │  string → tokens │   → [WORD("ls"), WORD("-la"), PIPE,
    └────────┬─────────┘      WORD("grep"), WORD("foo"),
             │                REDIR_OUT, WORD("out.txt")]
             ▼
    ┌─────────────────┐
    │     Parser       │   tokens → Pipeline (list of Commands)
    │  tokens → AST    │
    └────────┬─────────┘
             │
             ▼
    ┌─────────────────┐
    │    Executor      │   Pipeline → fork/pipe/dup2/exec
    │  AST → processes │
    └────────┬─────────┘
             │
     ┌───────┴────────┐
     ▼                ▼
  Builtins       External commands
  (cd, echo…)    (execvp → kernel)
```

The three components are **independent** — the Lexer does not know about the Executor, and the Parser does not call `fork`. This separation makes each stage unit-testable.

---

## 4. Data Structures

### `include/lexer.h`

```cpp
#pragma once
#include <string>
#include <vector>

enum class TokenType {
    WORD,        // any word: command name, argument, filename
    PIPE,        // |
    REDIR_IN,    // <
    REDIR_OUT,   // >
    REDIR_APPEND,// >>
    AND,         // &&
    OR,          // ||
    SEMICOLON,   // ;
    BACKGROUND,  // &
    HEREDOC,     // <<
    END,         // end of input
};

struct Token {
    TokenType type;
    std::string value;  // meaningful for WORD tokens
};

class Lexer {
public:
    explicit Lexer(std::string input);
    std::vector<Token> tokenize();

private:
    std::string input_;
    size_t pos_ = 0;

    void skip_whitespace();
    Token read_word();
    Token read_operator();
    char peek() const;
    char advance();
};
```

**Design notes:**
- `TokenType` is an `enum class` (not a plain `enum`) — avoids namespace pollution and is C++11 best practice.
- `Token` is a plain data struct — no inheritance, no virtuals — keeps it simple and cache-friendly.
- Lexer takes ownership of the input string by value → the caller's string is never mutated.

---

### `include/parser.h`

```cpp
#pragma once
#include "lexer.h"
#include <vector>
#include <string>
#include <optional>

enum class RedirType { IN, OUT, APPEND, HEREDOC };

struct Redirect {
    RedirType  type;
    std::string file;   // filename (or heredoc delimiter)
};

struct Command {
    std::vector<std::string> args;      // argv[0] = command name
    std::vector<Redirect>    redirs;    // per-command redirections
    bool                     background = false;
};

// A Pipeline is a list of commands connected by pipes:  cmd1 | cmd2 | cmd3
struct Pipeline {
    std::vector<Command> commands;
    bool                 background = false;   // trailing &
};

// A CommandList is commands separated by ;  &&  ||
// For MVP you can flatten this to just a vector<Pipeline>
struct CommandList {
    struct Entry {
        Pipeline    pipeline;
        std::string connector; // ";", "&&", "||", or "" for last
    };
    std::vector<Entry> entries;
};

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    CommandList parse();

private:
    std::vector<Token> tokens_;
    size_t pos_ = 0;

    Token        peek() const;
    Token        consume();
    bool         at_end() const;
    Pipeline     parse_pipeline();
    Command      parse_command();
    std::optional<Redirect> try_parse_redirect();
};
```

**Design notes:**
- `Command`, `Pipeline`, `CommandList` form a simple AST — no heap allocation, all value types.
- `std::optional<Redirect>` makes intent clear: "there may or may not be a redirect here."
- The parser does **not** call `fork` or touch file descriptors — pure data transformation.

---

### `include/jobs.h`

```cpp
#pragma once
#include <sys/types.h>
#include <string>
#include <vector>

enum class JobStatus { RUNNING, STOPPED, DONE };

struct Job {
    int         id;           // shell job number (1, 2, 3, …)
    pid_t       pgid;         // process group ID of the pipeline
    std::string command_str;  // original command line (for display)
    JobStatus   status = JobStatus::RUNNING;
    std::vector<pid_t> pids;  // one per process in the pipeline
};

class JobTable {
public:
    Job&  add(pid_t pgid, std::string cmd, std::vector<pid_t> pids);
    Job*  find_by_pgid(pid_t pgid);
    Job*  find_by_id(int id);
    void  update_statuses();   // call after waitpid(-1, WNOHANG)
    void  remove_done();
    void  print_jobs() const;

private:
    std::vector<Job> jobs_;
    int next_id_ = 1;
};
```

---

## 5. Stage 1 — Lexer

### Implementation: `src/lexer.cpp`

```cpp
#include "lexer.h"
#include <stdexcept>

Lexer::Lexer(std::string input) : input_(std::move(input)) {}

char Lexer::peek() const {
    return pos_ < input_.size() ? input_[pos_] : '\0';
}

char Lexer::advance() {
    return input_[pos_++];
}

void Lexer::skip_whitespace() {
    while (pos_ < input_.size() && std::isspace(static_cast<unsigned char>(input_[pos_])))
        ++pos_;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (true) {
        skip_whitespace();
        if (pos_ >= input_.size()) {
            tokens.push_back({TokenType::END, ""});
            break;
        }
        char c = peek();
        if (c == '|') {
            advance();
            if (peek() == '|') { advance(); tokens.push_back({TokenType::OR, "||"}); }
            else                              tokens.push_back({TokenType::PIPE, "|"});
        } else if (c == '&') {
            advance();
            if (peek() == '&') { advance(); tokens.push_back({TokenType::AND, "&&"}); }
            else                              tokens.push_back({TokenType::BACKGROUND, "&"});
        } else if (c == ';') {
            advance(); tokens.push_back({TokenType::SEMICOLON, ";"});
        } else if (c == '<') {
            advance();
            if (peek() == '<') { advance(); tokens.push_back({TokenType::HEREDOC, "<<"});  }
            else                              tokens.push_back({TokenType::REDIR_IN, "<"});
        } else if (c == '>') {
            advance();
            if (peek() == '>') { advance(); tokens.push_back({TokenType::REDIR_APPEND, ">>"});  }
            else                              tokens.push_back({TokenType::REDIR_OUT, ">"});
        } else {
            tokens.push_back(read_word());
        }
    }
    return tokens;
}

Token Lexer::read_word() {
    std::string value;
    bool in_single = false, in_double = false;
    while (pos_ < input_.size()) {
        char c = peek();
        if (c == '\'' && !in_double) { in_single = !in_single; advance(); continue; }
        if (c == '"'  && !in_single) { in_double = !in_double; advance(); continue; }
        if (!in_single && !in_double) {
            if (std::isspace(static_cast<unsigned char>(c))) break;
            if (c=='|'||c=='&'||c==';'||c=='<'||c=='>') break;
        }
        if (c == '\\' && !in_single && pos_+1 < input_.size()) {
            advance();  // skip backslash
            value += advance();
            continue;
        }
        value += advance();
    }
    return {TokenType::WORD, value};
}
```

**What makes this good:**

| Practice | Why |
|----------|-----|
| `static_cast<unsigned char>` before `std::isspace` | Avoids UB on platforms where `char` is signed |
| Single/double quote state tracked as bools, not a stack | Sufficient for POSIX shell quoting rules |
| Backslash handling inside `read_word` | Escape sequences work correctly (`echo hello\ world`) |
| No heap allocation per token | `std::string` small-string optimisation keeps short tokens on the stack |

---

## 6. Stage 2 — Parser

### Implementation: `src/parser.cpp`

```cpp
#include "parser.h"
#include <stdexcept>

Parser::Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)) {}

Token Parser::peek() const {
    return tokens_[pos_];
}

Token Parser::consume() {
    return tokens_[pos_++];
}

bool Parser::at_end() const {
    return tokens_[pos_].type == TokenType::END;
}

CommandList Parser::parse() {
    CommandList cl;
    while (!at_end()) {
        CommandList::Entry entry;
        entry.pipeline = parse_pipeline();
        if (!at_end() && (peek().type == TokenType::SEMICOLON ||
                          peek().type == TokenType::AND       ||
                          peek().type == TokenType::OR)) {
            entry.connector = consume().value;
        }
        cl.entries.push_back(std::move(entry));
        if (at_end()) break;
    }
    return cl;
}

Pipeline Parser::parse_pipeline() {
    Pipeline p;
    p.commands.push_back(parse_command());
    while (!at_end() && peek().type == TokenType::PIPE) {
        consume(); // eat '|'
        p.commands.push_back(parse_command());
    }
    if (!at_end() && peek().type == TokenType::BACKGROUND) {
        consume();
        p.background = true;
    }
    return p;
}

Command Parser::parse_command() {
    Command cmd;
    while (!at_end()) {
        auto redir = try_parse_redirect();
        if (redir) {
            cmd.redirs.push_back(*redir);
            continue;
        }
        TokenType t = peek().type;
        if (t == TokenType::WORD) {
            cmd.args.push_back(consume().value);
        } else {
            break; // hit |, &, ;, &&, || → stop this command
        }
    }
    // redirections can appear after args too: "cat foo.txt > out"
    while (!at_end()) {
        auto redir = try_parse_redirect();
        if (!redir) break;
        cmd.redirs.push_back(*redir);
    }
    return cmd;
}

std::optional<Redirect> Parser::try_parse_redirect() {
    TokenType t = peek().type;
    if (t == TokenType::REDIR_IN || t == TokenType::REDIR_OUT ||
        t == TokenType::REDIR_APPEND || t == TokenType::HEREDOC) {
        consume(); // eat the operator
        if (at_end() || peek().type != TokenType::WORD)
            throw std::runtime_error("syntax error: expected filename after redirect");
        RedirType rt = (t == TokenType::REDIR_IN)     ? RedirType::IN     :
                       (t == TokenType::REDIR_OUT)    ? RedirType::OUT    :
                       (t == TokenType::REDIR_APPEND) ? RedirType::APPEND :
                                                        RedirType::HEREDOC;
        return Redirect{rt, consume().value};
    }
    return std::nullopt;
}
```

**What makes this good:**

| Practice | Why |
|----------|-----|
| Recursive descent — one function per grammar rule | Each function is independently readable and testable |
| `std::optional` return from `try_parse_redirect` | Avoids sentinel/null-pointer patterns; communicates intent clearly |
| Exception on syntax error | Clean error path instead of silent data corruption |
| No static variables | Thread-safe (each Parser is independent state) |

---

## 7. Stage 3 — Executor

This is the heart of the shell. Get the file descriptor plumbing right.

### `include/executor.h`

```cpp
#pragma once
#include "parser.h"
#include "jobs.h"

class Executor {
public:
    explicit Executor(JobTable& job_table);

    // Execute one CommandList.  Returns exit status of last foreground pipeline.
    int execute(const CommandList& cl);

private:
    JobTable& jobs_;

    int  execute_pipeline(const Pipeline& p);
    int  execute_command(const Command& cmd, int fd_in, int fd_out);
    bool execute_builtin(const Command& cmd);
    void apply_redirects(const Command& cmd);
    void expand_variables(Command& cmd);
};
```

### Core pipeline execution: `src/executor.cpp`

```cpp
#include "executor.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

Executor::Executor(JobTable& job_table) : jobs_(job_table) {}

int Executor::execute(const CommandList& cl) {
    int last_status = 0;
    for (size_t i = 0; i < cl.entries.size(); ++i) {
        const auto& entry = cl.entries[i];
        if (i > 0) {
            const std::string& prev_conn = cl.entries[i-1].connector;
            if (prev_conn == "&&" && last_status != 0) continue;
            if (prev_conn == "||" && last_status == 0) continue;
        }
        last_status = execute_pipeline(entry.pipeline);
    }
    return last_status;
}

int Executor::execute_pipeline(const Pipeline& p) {
    size_t n = p.commands.size();
    if (n == 0) return 0;

    // Single command: check for builtin first
    if (n == 1 && !p.background) {
        if (execute_builtin(p.commands[0])) return 0;
    }

    // Create n-1 pipes
    // pipe_fds[i] = { read_end, write_end } connecting cmd[i] → cmd[i+1]
    std::vector<std::array<int,2>> pipe_fds(n - 1);
    for (auto& pf : pipe_fds) {
        if (pipe(pf.data()) < 0)
            throw std::runtime_error(std::string("pipe: ") + strerror(errno));
    }

    std::vector<pid_t> pids;
    pid_t pgid = 0;

    for (size_t i = 0; i < n; ++i) {
        int fd_in  = (i == 0)   ? STDIN_FILENO  : pipe_fds[i-1][0];
        int fd_out = (i == n-1) ? STDOUT_FILENO : pipe_fds[i][1];

        pid_t pid = fork();
        if (pid < 0)
            throw std::runtime_error(std::string("fork: ") + strerror(errno));

        if (pid == 0) {
            // ── CHILD ──────────────────────────────────────────────
            // Put the child in its own process group (first child creates it)
            pid_t my_pgid = (pgid == 0) ? getpid() : pgid;
            setpgid(0, my_pgid);

            // Wire up stdin/stdout to pipe ends
            if (fd_in != STDIN_FILENO) {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            if (fd_out != STDOUT_FILENO) {
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            // Close all pipe ends the child doesn't need
            for (auto& pf : pipe_fds) { close(pf[0]); close(pf[1]); }

            apply_redirects(p.commands[i]);
            execute_command(p.commands[i], STDIN_FILENO, STDOUT_FILENO);
            // execute_command calls execvp — only reaches here on error
            std::cerr << p.commands[i].args[0] << ": command not found\n";
            _exit(127);
        }

        // ── PARENT ──────────────────────────────────────────────
        if (pgid == 0) pgid = pid;
        setpgid(pid, pgid); // also set from parent to avoid race
        pids.push_back(pid);
    }

    // Close all pipe ends in the parent
    for (auto& pf : pipe_fds) { close(pf[0]); close(pf[1]); }

    if (p.background) {
        // Register as a background job and return immediately
        std::string cmd_str = p.commands[0].args.empty() ? "" : p.commands[0].args[0];
        jobs_.add(pgid, cmd_str, pids);
        std::cout << "[" << jobs_.find_by_pgid(pgid)->id << "] " << pgid << "\n";
        return 0;
    }

    // Give the process group the terminal and wait
    tcsetpgrp(STDIN_FILENO, pgid);
    int status = 0;
    for (pid_t pid : pids)
        waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp()); // reclaim terminal

    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

void Executor::apply_redirects(const Command& cmd) {
    for (const auto& r : cmd.redirs) {
        int fd = -1;
        if (r.type == RedirType::IN) {
            fd = open(r.file.c_str(), O_RDONLY);
            if (fd < 0) { perror(r.file.c_str()); _exit(1); }
            dup2(fd, STDIN_FILENO);
        } else if (r.type == RedirType::OUT) {
            fd = open(r.file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) { perror(r.file.c_str()); _exit(1); }
            dup2(fd, STDOUT_FILENO);
        } else if (r.type == RedirType::APPEND) {
            fd = open(r.file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) { perror(r.file.c_str()); _exit(1); }
            dup2(fd, STDOUT_FILENO);
        }
        if (fd >= 0) close(fd);
    }
}

int Executor::execute_command(const Command& cmd, int /*fd_in*/, int /*fd_out*/) {
    if (cmd.args.empty()) return 0;
    // Build argv for execvp
    std::vector<char*> argv;
    argv.reserve(cmd.args.size() + 1);
    for (const auto& s : cmd.args)
        argv.push_back(const_cast<char*>(s.c_str()));
    argv.push_back(nullptr);
    execvp(argv[0], argv.data());
    return -1; // execvp only returns on error
}
```

**Critical file-descriptor rules (memorise these):**

```
Rule 1 — Always close BOTH ends of every pipe in the parent after forking.
         If you forget, the child's stdin will never see EOF.

Rule 2 — In the child, dup2 THEN close the original fd.
         Never close fd_in before dup2(fd_in, STDIN_FILENO).

Rule 3 — Close all pipe fds the child doesn't use.
         A child in cmd[0] must close pipe_fds[1][0] and pipe_fds[1][1], etc.

Rule 4 — Use _exit() in the child, not exit().
         exit() flushes stdio buffers which can corrupt the parent's output.

Rule 5 — Call setpgid() from BOTH parent and child (race-free approach).
         The child calls setpgid(0, pgid) and the parent calls setpgid(pid, pgid).
```

---

## 8. Stage 4 — Built-in Commands

Builtins must run in the **shell process** (not a fork) because they modify shell state (cwd, env, exit code).

### `include/builtins.h`

```cpp
#pragma once
#include "parser.h"
#include "jobs.h"
#include <functional>
#include <unordered_map>
#include <string>

class Builtins {
public:
    explicit Builtins(JobTable& jobs);

    // Returns true if cmd.args[0] is a builtin.  Executes it and sets *exit_status.
    bool dispatch(const Command& cmd, int* exit_status);

private:
    JobTable& jobs_;

    int builtin_cd(const Command& cmd);
    int builtin_pwd(const Command& cmd);
    int builtin_echo(const Command& cmd);
    int builtin_export(const Command& cmd);
    int builtin_unset(const Command& cmd);
    int builtin_jobs(const Command& cmd);
    int builtin_fg(const Command& cmd);
    int builtin_bg(const Command& cmd);
    int builtin_exit(const Command& cmd);
};
```

### Implementation notes for each builtin

```cpp
// cd: chdir() + update $PWD and $OLDPWD
int Builtins::builtin_cd(const Command& cmd) {
    const char* path = (cmd.args.size() > 1) ? cmd.args[1].c_str()
                                              : getenv("HOME");
    if (!path) { std::cerr << "cd: HOME not set\n"; return 1; }
    char old_pwd[PATH_MAX];
    getcwd(old_pwd, sizeof(old_pwd));
    if (chdir(path) != 0) { perror("cd"); return 1; }
    setenv("OLDPWD", old_pwd, 1);
    char new_pwd[PATH_MAX];
    setenv("PWD", getcwd(new_pwd, sizeof(new_pwd)), 1);
    return 0;
}

// echo: print args separated by spaces; -n suppresses trailing newline
int Builtins::builtin_echo(const Command& cmd) {
    bool newline = true;
    size_t start = 1;
    if (cmd.args.size() > 1 && cmd.args[1] == "-n") { newline = false; start = 2; }
    for (size_t i = start; i < cmd.args.size(); ++i) {
        if (i > start) std::cout << ' ';
        std::cout << cmd.args[i];
    }
    if (newline) std::cout << '\n';
    return 0;
}

// export: set environment variable
int Builtins::builtin_export(const Command& cmd) {
    for (size_t i = 1; i < cmd.args.size(); ++i) {
        const std::string& s = cmd.args[i];
        auto eq = s.find('=');
        if (eq == std::string::npos) {
            // export NAME  (mark as exported; no assignment)
            // For simplicity: just ensure it exists
        } else {
            std::string name  = s.substr(0, eq);
            std::string value = s.substr(eq + 1);
            setenv(name.c_str(), value.c_str(), 1);
        }
    }
    return 0;
}
```

---

## 9. Stage 5 — Signal Handling

### Rules

```
Signal       Who handles it        How
─────────────────────────────────────────────────────────────────────
SIGINT       Shell ignores it;     SIG_IGN in shell, default in child
             child gets it
SIGQUIT      Same as SIGINT
SIGTSTP      Shell ignores it;     SIG_IGN in shell, default in child
             terminal sends to fg process group
SIGCHLD      Shell catches it      Reap zombie children with waitpid
SIGTTOU      Shell ignores it      Avoids SIGTTOU when calling tcsetpgrp
SIGTTIN      Shell ignores it      Same
```

### Implementation: `src/main.cpp` signal setup

```cpp
#include <signal.h>
#include <unistd.h>

static void setup_signals() {
    // Shell ignores these; child processes inherit SIG_DFL (reset before exec)
    signal(SIGINT,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    // SIGCHLD: use SA_RESTART and SA_NOCLDSTOP to avoid interrupted read()
    struct sigaction sa{};
    sa.sa_handler = [](int) {
        // Reap all completed children without blocking
        int status;
        while (waitpid(-1, &status, WNOHANG | WUNTRACED) > 0) {}
    };
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, nullptr);
}

// In child process, before exec, reset signals to defaults:
static void reset_signals_for_child() {
    signal(SIGINT,  SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
}
```

**Why `SA_RESTART` matters:**  
Without it, `SIGCHLD` can interrupt `read()` (your prompt's `getline` call), causing the shell to print a spurious error. `SA_RESTART` makes the kernel restart the interrupted syscall automatically.

---

## 10. Stage 6 — Job Control

### The REPL loop with job control

```cpp
// src/main.cpp  (main loop sketch)

int main() {
    Shell shell;         // owns Lexer, Parser, Executor, JobTable, Builtins
    setup_signals();
    shell.put_in_foreground();   // tcsetpgrp(STDIN_FILENO, getpgrp())

    std::string line;
    while (true) {
        shell.print_prompt();         // "[zsh]$ "
        if (!std::getline(std::cin, line)) break;  // EOF → exit
        if (line.empty()) continue;

        try {
            auto tokens   = Lexer(line).tokenize();
            auto cmd_list = Parser(std::move(tokens)).parse();
            shell.execute(cmd_list);
        } catch (const std::exception& e) {
            std::cerr << "error: " << e.what() << "\n";
        }

        shell.reap_finished_jobs();   // print "[1] Done   sleep 5" etc.
    }
    return 0;
}
```

### `fg` and `bg` implementation

```cpp
int Builtins::builtin_fg(const Command& cmd) {
    int id = (cmd.args.size() > 1) ? std::stoi(cmd.args[1]) : -1;
    Job* job = (id == -1) ? jobs_.most_recent() : jobs_.find_by_id(id);
    if (!job) { std::cerr << "fg: no such job\n"; return 1; }

    // Give the job the terminal
    tcsetpgrp(STDIN_FILENO, job->pgid);
    // Resume it if stopped
    killpg(job->pgid, SIGCONT);
    job->status = JobStatus::RUNNING;

    // Wait for it to finish or stop
    int status;
    waitpid(-job->pgid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());  // take terminal back

    if (WIFSTOPPED(status)) {
        job->status = JobStatus::STOPPED;
        std::cout << "\n[" << job->id << "]+ Stopped   " << job->command_str << "\n";
    } else {
        job->status = JobStatus::DONE;
    }
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int Builtins::builtin_bg(const Command& cmd) {
    int id = (cmd.args.size() > 1) ? std::stoi(cmd.args[1]) : -1;
    Job* job = (id == -1) ? jobs_.most_recent_stopped() : jobs_.find_by_id(id);
    if (!job) { std::cerr << "bg: no such job\n"; return 1; }
    killpg(job->pgid, SIGCONT);
    job->status = JobStatus::RUNNING;
    std::cout << "[" << job->id << "]+ " << job->command_str << " &\n";
    return 0;
}
```

---

## 11. Error Handling Patterns

### Rule: never silently swallow errors

```cpp
// BAD — silent failure
fork();

// GOOD — always check syscall return values
pid_t pid = fork();
if (pid < 0) throw std::runtime_error(std::string("fork: ") + strerror(errno));
```

### Rule: use RAII for file descriptors

```cpp
// RAII file descriptor wrapper — prevents leaks
struct FD {
    int fd;
    explicit FD(int fd) : fd(fd) {}
    ~FD() { if (fd >= 0) close(fd); }
    FD(const FD&) = delete;
    FD& operator=(const FD&) = delete;
    FD(FD&& o) : fd(o.fd) { o.fd = -1; }
    operator int() const { return fd; }
    int release() { int r = fd; fd = -1; return r; }
};

// Usage:
FD read_end(pipe_fds[i][0]);   // auto-closed when goes out of scope
FD write_end(pipe_fds[i][1]);
```

### Rule: `_exit` in children, `exit` only in the shell

```cpp
// In child process (after fork), ALWAYS use _exit(), not exit()
// exit() flushes stdio buffers inherited from the parent → double-output bugs
_exit(127);  // command not found
```

### Rule: check that `cmd.args` is non-empty before accessing `[0]`

```cpp
if (cmd.args.empty()) {
    // empty command (e.g. a bare redirect: "< file")
    return;
}
```

---

## 12. Testing Strategy

### Automated test format

Each test file in `tests/` follows this pattern:

```bash
#!/usr/bin/env bash
# tests/t02_pipes.sh

SHELL_BINARY="${1:-./build/mysh}"
PASS=0; FAIL=0

check() {
    local desc="$1" expected="$2"
    local actual
    actual=$(echo "$3" | "$SHELL_BINARY" 2>&1)
    if [ "$actual" = "$expected" ]; then
        echo "  PASS: $desc"
        ((PASS++))
    else
        echo "  FAIL: $desc"
        echo "    expected: $(echo "$expected" | head -3)"
        echo "    actual:   $(echo "$actual"   | head -3)"
        ((FAIL++))
    fi
}

echo "=== Pipe tests ==="
check "simple pipe"       "hello"               'echo hello | cat'
check "two-stage pipe"    "HELLO"               'echo hello | tr a-z A-Z'
check "three-stage pipe"  "3"                   'echo -e "a\nb\nc" | wc -l | tr -d " "'
check "pipe with redir"   "hello"               'echo hello | cat > /tmp/sh_test_out.txt && cat /tmp/sh_test_out.txt'

echo "Passed: $PASS  Failed: $FAIL"
[ "$FAIL" -eq 0 ]
```

### Master runner: `tests/run_tests.sh`

```bash
#!/usr/bin/env bash
SHELL_BINARY="${1:-./build/mysh}"
TOTAL_FAIL=0
for t in tests/t*.sh; do
    bash "$t" "$SHELL_BINARY" || ((TOTAL_FAIL++))
done
echo "=== Total suite: $TOTAL_FAIL test files failed ==="
exit "$TOTAL_FAIL"
```

### What to test

| Test file | Covers |
|-----------|--------|
| `t01_basic_commands.sh` | `echo`, `ls`, `pwd`, exit status `$?` |
| `t02_pipes.sh` | 1-pipe, 2-pipe, 3-pipe, pipe + redir |
| `t03_redirections.sh` | `>`, `>>`, `<`, order independence |
| `t04_builtins.sh` | `cd`, `export`, `unset`, `echo -n` |
| `t05_job_control.sh` | Background `&`, `jobs` output, `fg`, `bg` |
| `t06_edge_cases.sh` | Empty input, missing file, bad command, `&&`, `\|\|` |

### Valgrind check

```bash
valgrind --leak-check=full --error-exitcode=1 \
    ./build/mysh <<< "echo hello | cat"
```

Add this to your CI (GitHub Actions) to catch memory leaks automatically.

---

## 13. Code-Quality Checklist

Use this before each commit:

### Naming conventions

```
Files:       snake_case.cpp / snake_case.h        (lexer.cpp, job_table.h)
Classes:     PascalCase                            (Lexer, JobTable, Pipeline)
Methods:     snake_case                            (tokenize(), execute_pipeline())
Members:     snake_case with trailing underscore   (tokens_, pos_, jobs_)
Constants:   SCREAMING_SNAKE_CASE                  (STDIN_FILENO — from POSIX)
Enums:       enum class + PascalCase values        (TokenType::PIPE)
```

### C++ best practices checklist

- [ ] All `std::string` parameters passed by `const&` or moved with `std::move`
- [ ] Every `fork()`, `pipe()`, `dup2()`, `open()` return value checked
- [ ] Every `close()` called exactly once per fd (use RAII `FD` wrapper)
- [ ] Child always uses `_exit()`, never `exit()`
- [ ] `setpgid()` called from both parent and child (avoids race)
- [ ] Signals reset to `SIG_DFL` in child before `execvp`
- [ ] `execvp` argv array terminated with `nullptr`
- [ ] `argv` `const_cast<char*>` only because `execvp` takes `char* const*` (safe — exec doesn't mutate them)
- [ ] No global mutable state except the `JobTable` (and even that is owned by `Shell`)
- [ ] `[[nodiscard]]` on functions whose return value must be checked
- [ ] `noexcept` on functions that must not throw (e.g. signal handlers)

### Memory leak prevention

```cpp
// BAD: raw new in a loop
char** argv = new char*[cmd.args.size() + 1];

// GOOD: stack-allocated vector with .data()
std::vector<char*> argv;
for (const auto& s : cmd.args) argv.push_back(const_cast<char*>(s.c_str()));
argv.push_back(nullptr);
execvp(argv[0], argv.data());
```

### Compile flags to use

```cmake
# CMakeLists.txt
target_compile_options(mysh PRIVATE
    -Wall -Wextra -Wpedantic
    -Wshadow -Wnon-virtual-dtor
    -Wold-style-cast -Wcast-align
    -Wunused -Woverloaded-virtual
    -fsanitize=address,undefined   # in Debug build
)
target_link_options(mysh PRIVATE -fsanitize=address,undefined)
```

These flags will catch:
- Signed integer overflow (UBSAN)
- Use-after-free, heap overflow (ASAN)
- Shadowed variables (`-Wshadow`)
- Unused parameters and return values (`-Wunused`)

---

## 14. Common Pitfalls

### Pitfall 1 — Zombie processes

**Symptom:** `ps aux | grep Z` shows zombie children.  
**Cause:** Parent never calls `waitpid` after child exits.  
**Fix:** In the SIGCHLD handler, call `waitpid(-1, &status, WNOHANG)` in a loop until it returns 0 or -1.

```cpp
// SIGCHLD handler — reap ALL completed children
signal(SIGCHLD, [](int) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {}
});
```

---

### Pitfall 2 — Pipeline hangs (reader never sees EOF)

**Symptom:** `echo hello | cat` hangs forever.  
**Cause:** Parent forgot to close the write end of the pipe after forking.  
**Fix:** After all `fork()` calls, close every `pipe_fds[i][0]` and `pipe_fds[i][1]` in the parent.

```
Before fix:
  Parent: [read0, write0, read1, write1] ← write0 still open → cat never sees EOF

After fix:
  Parent: [all closed]                   → cat sees EOF when echo exits  ✓
```

---

### Pitfall 3 — `Ctrl-C` kills the shell

**Symptom:** Pressing `Ctrl-C` while a command is running also kills the shell.  
**Cause:** Shell and child are in the same process group.  
**Fix:**  
1. Shell ignores `SIGINT` (`signal(SIGINT, SIG_IGN)`).  
2. Each pipeline gets its own process group (`setpgid`).  
3. Terminal is given to the child's process group (`tcsetpgrp`).  
4. Child resets `SIGINT` to `SIG_DFL` before `exec`.

---

### Pitfall 4 — `cd` doesn't work (run in a child)

**Symptom:** `cd /tmp` appears to succeed but the prompt is still in the old directory.  
**Cause:** `cd` was `fork()`-ed and ran in a child process; `chdir()` only affects the child's cwd.  
**Fix:** Check for builtins **before** calling `fork()`. Builtins run in the shell process.

---

### Pitfall 5 — `export VAR=value` doesn't propagate to subsequent commands

**Cause:** Same as pitfall 4 — `setenv` in a child doesn't affect the parent's environment.  
**Fix:** `export` is a builtin; it must run in the shell process.

---

### Pitfall 6 — `execvp` argv not null-terminated

**Symptom:** Random crashes or garbage output.  
**Cause:** Missing `argv.push_back(nullptr)` before `execvp`.  
**Fix:**
```cpp
argv.push_back(nullptr);  // POSIX requires argv[argc] == NULL
execvp(argv[0], argv.data());
```

---

### Pitfall 7 — Forgetting `close(fd)` after `dup2`

**Symptom:** File descriptor table fills up after many commands.  
**Cause:**
```cpp
// WRONG — the original fd is still open after dup2
dup2(fd, STDIN_FILENO);

// RIGHT
dup2(fd, STDIN_FILENO);
close(fd);               // original fd no longer needed
```

---

## 15. Suggested Commit Milestones

Structure your git history to tell a clear story to any engineer reading it:

```
commit 1 — "Project skeleton: CMakeLists, header stubs, empty .cpp files"
commit 2 — "Lexer: tokenize words, pipes, redirections, operators"
commit 3 — "Lexer: single/double quote and backslash handling"
commit 4 — "Parser: parse_command and try_parse_redirect"
commit 5 — "Parser: parse_pipeline (| chaining)"
commit 6 — "Parser: parse command list (&&, ||, ;)"
commit 7 — "Executor: fork + execvp for single external command"
commit 8 — "Executor: pipe chaining (n-command pipeline)"
commit 9 — "Executor: I/O redirection (<, >, >>)"
commit 10 — "Builtins: cd, pwd, echo, exit"
commit 11 — "Builtins: export, unset"
commit 12 — "Signal handling: SIGINT/SIGQUIT/SIGTSTP ignored in shell"
commit 13 — "Signal handling: SIGCHLD handler reaps zombies"
commit 14 — "Job control: & background, jobs builtin"
commit 15 — "Job control: fg and bg builtins"
commit 16 — "Tests: t01 basic commands"
commit 17 — "Tests: t02 pipes, t03 redirections, t04 builtins, t05 job control"
commit 18 — "README: demo GIF, build instructions, feature table"
```

Each commit should compile and pass all existing tests — no broken intermediate states.

---

## 16. Key References

| Resource | What it covers |
|----------|---------------|
| `man 2 fork` / `man 2 execvp` / `man 2 pipe` / `man 2 dup2` | Primary system calls |
| `man 2 waitpid` / `man 2 kill` / `man 2 setpgid` / `man 2 tcsetpgrp` | Job control system calls |
| [CS:APP Chapter 8 — Exceptional Control Flow](https://csapp.cs.cmu.edu/) | Best textbook explanation of fork/exec/signal |
| [The GNU C Library — Job Control](https://www.gnu.org/software/libc/manual/html_node/Job-Control.html) | Definitive reference for correct job control |
| [Writing Your Own Shell (Stephen Brennan)](https://brennan.io/2015/01/16/write-a-shell-in-c/) | Short, accurate C tutorial |
| [dash source code](https://git.kernel.org/pub/scm/utils/dash/dash.git) | Real POSIX shell in ~15 k lines of C — readable reference |
| [Crafting Interpreters — Scanning chapter](https://craftinginterpreters.com/scanning.html) | Best explanation of lexer design |
| POSIX spec — Shell Grammar | https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html |

---

*Last updated: 2026-03-17*
