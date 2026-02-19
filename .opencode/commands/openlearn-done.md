---
description: Complete task with 6 Gates verification
agent: mentor
---

# /openlearn-done

Complete a task and run all 6 Gates for quality verification.

## Flow

1. **Identify completed work**
   - Ask: "What are you completing?"
     - Task from spec
     - Bug fix
     - Feature
     - Refactor
   - Read relevant spec if from active spec

2. **Gather changes**
   - Run `git log --oneline -5`
   - Run `git diff --name-only HEAD~1` or `git status`
   - Ask: "What are the key files to review?"
   - Read the key files

3. **Run 6 Gates sequentially**

   Use `task` tool to invoke each gate agent:
   
   ```
   task(description="Run ownership gate", prompt="@ownership-gate", subagent_type="general")
   ```

   ### Gate 1: @ownership-gate (BLOCKING)
   - Verify student understands their code
   - Score 0-100, must be ≥75%
   - If failed: 
     1. Show score and what needs improvement
     2. Provide study resources
     3. Ask: "Ready to retry with a different question?"
     4. Re-invoke gate with new question
     5. Repeat until passed or student gives up
   
   ### Gate 2: @security-gate (BLOCKING)
   - Review for security issues
   - Score 0-100, must be ≥75%
   - If failed:
     1. Show score and critical issues
     2. Explain security risks
     3. Provide secure coding resources
     4. Ask: "Have you fixed the issues?"
     5. Re-invoke gate for re-review
     6. Repeat until passed or student gives up
   
   ### Gate 3: @error-gate
   - Check error handling
   - Non-blocking, report issues
   
   ### Gate 4: @performance-gate
   - Review performance
   - Non-blocking, report issues
   
   ### Gate 5: @fundamentals-gate
   - Check code quality
   - Non-blocking, report issues
   
   ### Gate 6: @testing-gate
   - Verify test coverage
   - Non-blocking, suggest improvements

4. **Code review summary**
   - Show all gate scores
   - Highlight any blocking failures
   - List non-blocking recommendations

5. **Update spec**
   - If from active spec, mark task complete in tasks.md

6. **Show completion summary**
   - ✅ All gates passed OR
   - 🔴 Blocking gates failed - fix and retry

## Implementation Notes

When invoking gates, pass the relevant file paths and context:

```
task(
  description="Run ownership gate",
  prompt="""
  @ownership-gate
  
  Files to review:
  - /path/to/file1.js
  - /path/to/file2.js
  
  Task: [task description]
  """,
  subagent_type="general"
)
```

For blocking gates that fail, implement retry logic:

```
while gate_score < 75:
  ask if ready to retry
  if yes:
    re-invoke gate
  else:
    break and report failure
```

## Example Session

```
Student: /openlearn-done

OpenLearn: What are you completing?
Student: The todo list component from phase 1

OpenLearn: Reading spec and key files...
[Reads spec.md, tasks.md, TodoList.jsx]

---
🔒 Running Gate 1: Ownership...
OpenLearn (@ownership-gate): Walk me through this code step by step.
Student: [Explains]
OpenLearn: Why did you choose useState here?
Student: [Explains]

🔒 Ownership Gate Score: 85/100 PASS
- Understanding: 22/25
- Trade-offs: 20/25
- Modifications: 22/25
- Alternatives: 21/25
---

🛡️ Running Gate 2: Security...
[Reviews code]
🛡️ Security Gate Score: 100/100 PASS
No security issues found.
---

⚠️ Running Gate 3: Error Handling...
⚠️ Error Handling Gate: 1 issue found
- Line 23: Empty catch block
  Consider: catch (e) { console.error('Failed to save:', e); }
---

⚡ Running Gate 4: Performance...
⚡ Performance Gate: No issues
---

📖 Running Gate 5: Fundamentals...
📖 Fundamentals Gate: 1 suggestion
- Function 'handleSubmit' is 60 lines
  Consider breaking into smaller functions
---

🧪 Running Gate 6: Testing...
🧪 Testing Gate: No tests found
💡 Testing opportunities:
- Test adding a todo
- Test toggling completion
- Test deleting a todo
---

Updating spec...
✅ Task marked complete in tasks.md

## Completion Summary

✅ All blocking gates PASSED

**Scores:**
- 🔒 Ownership: 85/100 ✅
- 🛡️ Security: 100/100 ✅
- ⚠️ Errors: 1 suggestion
- ⚡ Performance: Clean
- 📖 Fundamentals: 1 suggestion
- 🧪 Testing: Opportunities identified

**Recommendations:**
1. Add error handling to catch block
2. Refactor handleSubmit function
3. Consider adding tests

Next: Continue with next task or `/openlearn-feature` for new feature
```
