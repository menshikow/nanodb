---
description: Create feature specification using spec-driven development
agent: mentor
---

# /openlearn-feature

Plan a new feature using spec-driven development.

## Flow

1. **Check roadmap**
   - Read `.opencode/openlearn/product/roadmap.md`
   - If roadmap exists with incomplete phase:
     - Show current phase tasks
     - Ask: "Which feature are you implementing?"
   - If no roadmap: Ask for feature name

2. **Gather requirements**
   - Ask: "What should this feature do?"
   - Ask: "Who will use it?"
   - Ask: "What does success look like?"
   - Discuss edge cases

3. **Research with Context7** (if enabled)
   - Query Context7 for relevant documentation
   - Check for patterns and best practices
   - Review similar examples

4. **Socratic architecture discussion**
   - "What components will you need?"
   - "What data structures make sense?"
   - "What API endpoints are required?"
   - "How will state be managed?"

5. **Generate spec files**
   - Create `.opencode/openlearn/specs/active/phase-[N]-[name]/spec.md`
   - Create `.opencode/openlearn/specs/active/phase-[N]-[name]/design.md`
   - Create `.opencode/openlearn/specs/active/phase-[N]-[name]/tasks.md`

6. **Present for review**
   - Show generated specs
   - Ask for changes
   - Confirm or iterate

7. **Next steps**
   - "Ready to implement? Use `/openlearn-guide` if you need help"

## Example Session

```
Student: /openlearn-feature

OpenLearn: Checking roadmap...
[Reads roadmap.md]

OpenLearn: You're in Phase 1: Foundation. 
What feature are you implementing?
Student: Add a todo item

OpenLearn: What should this feature do?
Student: Let users type a task and add it to the list

OpenLearn: What does success look like?
Student: User can type, press enter or click add, see it in the list

--- Context7 Research ---
[If mode is auto, queries Context7 for React forms and state management]

OpenLearn: I see you'll need form handling. Let's discuss the approach.

--- Architecture Discussion ---

OpenLearn: What components do you think you'll need?
Student: An input field and a button

OpenLearn: Good! What about the list itself?
Student: Maybe a separate TodoList component?

OpenLearn: Exactly! How will the new todo get added to the list?
Student: Lift state up? Pass a function down?

OpenLearn: Perfect thinking! That's the React pattern.

--- Generating Specs ---

[Creates spec files]

OpenLearn: I've created your feature spec:

📄 spec.md - Requirements and acceptance criteria
📄 design.md - Technical approach  
📄 tasks.md - Implementation checklist

Would you like to review or change anything?

Student: Looks good!

OpenLearn: Great! Start with the first task. 
Use `/openlearn-guide` if you need help, `/openlearn-stuck` if you get stuck.
```
