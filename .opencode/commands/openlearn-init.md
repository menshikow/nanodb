---
description: Initialize OpenLearn project with mission, stack, and roadmap
agent: mentor
subtask: false
---

# /openlearn-init

Initialize a new OpenLearn project with profile setup, project definition, and configuration.

## Flow

1. **Check if already initialized**
   - Read `.opencode/openlearn/config.json`
   - If exists, ask if they want to reinitialize

2. **Profile setup** (Junior profile - fixed for v1)
   - Ask: "What's your coding background?"
     - Options: "Know basics (variables, functions, loops)", "Built a few projects"
   - Ask: "Do you like analogies when learning?"
     - Options: Yes/No

3. **Project questions**
   - Ask: "What problem are you solving?" (free text)
   - Ask: "Who is this for?"
     - Options: Myself learning, Portfolio project, Real users
   - Ask: "How will you know it's done?"
     - List 2-3 specific, measurable criteria

4. **Stack detection**
   - Check for existing files:
     - `package.json` → Node.js project
     - `Cargo.toml` → Rust project
     - `requirements.txt` → Python project
     - `go.mod` → Go project
     - Other typical files...
   - If no existing project detected:
     - Ask: "What stack do you want to use?"
     - Examples: React, Vue, Svelte, Vanilla JS, Python/Flask, etc.

5. **Context7 configuration**
   - Ask: "How should I use documentation?"
     - Auto: Automatically check official docs
     - Suggest: Ask before checking docs
     - Manual: Only check when you ask

6. **Generate outputs**
   - `.opencode/openlearn/config.json`
   - `.opencode/openlearn/product/mission.md`
   - `.opencode/openlearn/product/stack.md`
   - `.opencode/openlearn/product/roadmap.md`
   - Update `AGENTS.md` with OpenLearn behavior

7. **Confirm success**
   - Show summary of what was created
   - Next step: `/openlearn-feature`

## Example Session

```
Student: /openlearn-init

OpenLearn: Let's set up your OpenLearn project! I'll ask a few questions...

OpenLearn: What's your coding background?
Student: Know basics

OpenLearn: Do you like analogies when learning?
Student: Yes

OpenLearn: What problem are you solving?
Student: I want to build a todo app to track my daily tasks

OpenLearn: Who is this for?
Student: Portfolio project

OpenLearn: How will you know it's done?
Student: Can add tasks, mark complete, delete tasks, persist data

OpenLearn: I see you have a package.json. Using React/Vite setup. Correct?
Student: Yes

OpenLearn: How should I use documentation?
Student: Auto

[Generating files...]

✅ OpenLearn initialized!

Created:
- config.json
- mission.md  
- stack.md
- roadmap.md
- Updated AGENTS.md

Next: /openlearn-feature to plan your first feature
```
