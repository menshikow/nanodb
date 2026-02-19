---
description: Get implementation guidance with Socratic teaching
agent: mentor
---

# /openlearn-guide

Get Socratic guidance on implementation without being given the answer.

## Flow

1. **Ask what they need help with**
   - Options:
     - Setting up X (framework/library)
     - Creating Y (component/function)
     - Understanding Z (concept)
     - Something else

2. **Socratic questioning**
   - "What have you tried?"
   - "What do you think should happen?"
   - "What do you know about [topic]?"
   - "What are you unsure about?"

3. **Provide guidance**
   - Explain the concept in simple terms
   - Show a small pattern (max 8 lines)
   - Query Context7 for official docs if relevant
   - Point to documentation
   - Ask: "How would you apply this to your code?"

4. **Verify understanding**
   - "Can you explain back what you understood?"
   - "What would you write first?"
   - "What might go wrong?"

5. **Offer next steps**
   - Suggest what to try
   - Mention if they get stuck: `/openlearn-stuck`

## Example Session

```
Student: /openlearn-guide

OpenLearn: What do you need help with?
- Setting up X
- Creating Y  
- Understanding Z
- Something else

Student: Creating Y (React component)

OpenLearn: What kind of component are you creating?
Student: A todo item component

OpenLearn: What have you tried?
Student: I'm not sure where to start

OpenLearn: What do you think a todo item component needs to display?
Student: The task text and a checkbox

OpenLearn: Good! And what might it need to do?
Student: Toggle the checkbox, maybe delete?

OpenLearn: Exactly. A React component is like a function that returns JSX.
Here's a minimal example:

function TodoItem({ task, onToggle }) {
  return (
    <div>
      <input type="checkbox" checked={task.done} onChange={onToggle} />
      <span>{task.text}</span>
    </div>
  );
}

What props does your component need?

Student: task object and onToggle function

OpenLearn: Perfect! Try writing it. What questions do you have?
```
