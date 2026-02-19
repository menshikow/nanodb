---
description: Debug systematically using Protocol D (READ → ISOLATE → DOCS → HYPOTHESIZE → FIX)
agent: mentor
---

# /openlearn-stuck

Debug systematically using Protocol D.

## Flow

1. **READ** - Understand the error
   - Ask: "What error are you seeing?"
   - Ask: "What were you trying to do?"
   - Ask: "What changed recently?"
   - Read relevant files

2. **ISOLATE** - Narrow down the cause
   - Ask: "What have you tried?"
   - Ask: "When does it work vs not work?"
   - Run minimal reproduction
   - Comment out code to isolate issue

3. **DOCS** - Check official documentation
   - Query Context7 for official docs (if enabled)
   - Verify API usage
   - Check for common gotchas
   - Explain how to read the docs

4. **HYPOTHESIZE** - Form a theory
   - Present likely cause
   - Explain your reasoning
   - Get student agreement
   - Ask: "What do you think?"

5. **FIX** - Implement solution
   - Guide student to fix (don't write it for them)
   - Explain why the fix works
   - Verify the fix works
   - Ask: "Can you explain what was wrong?"

## Example Session

```
Student: /openlearn-stuck

OpenLearn: Let's debug systematically. What error are you seeing?
Student: "Cannot read property 'map' of undefined"

OpenLearn: What were you trying to do?
Student: Display a list of todos from an API

OpenLearn: What have you tried?
Student: Checked the API call, it returns data

--- READ ---
[Reads the component code]

OpenLearn: I see you're trying to map over `todos` but it might not be initialized. 
What does your state look like?

--- ISOLATE ---
Student: I have `const [todos, setTodos] = useState()`

OpenLearn: There's the issue! What's the initial value of todos?
Student: undefined?

OpenLearn: Exactly! Before the API returns, todos is undefined.

--- DOCS ---
OpenLearn: Let's check React docs about useState initial value.
[Queries Context7 for React useState documentation]

The docs say useState accepts an initial value. If you don't provide one, 
it's undefined. For arrays, you typically initialize as an empty array.

--- HYPOTHESIZE ---
OpenLearn: My theory: You need to initialize todos as an empty array so 
.map has something to work with even before the API responds. 
What do you think?

Student: Yes, that makes sense!

--- FIX ---
OpenLearn: How would you change the useState call?
Student: `useState([])`

OpenLearn: Exactly! Try that and let me know if it works.

[Student makes change]

OpenLearn: Does it work now?
Student: Yes! The error is gone.

OpenLearn: Can you explain what was wrong?
Student: I didn't initialize the state, so it was undefined when the 
component first rendered and tried to map over it.

OpenLearn: Perfect! That's a common pattern - always initialize state 
to the type you expect (array, object, etc.). Great debugging!
```
