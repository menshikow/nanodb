---
description: Help with documentation
agent: mentor
---

# /openlearn-docs

Get guidance on writing documentation.

## Flow

1. **Ask what needs documenting**
   - Component documentation
   - Function documentation
   - README
   - Architecture decision records

2. **Discuss documentation standards**
   - Who is the audience?
   - What level of detail?
   - Code comments vs external docs

3. **Guide through writing docs**
   - Explain good documentation patterns
   - Show examples
   - Student writes the docs

4. **Review documentation**
   - Is it clear?
   - Does it answer "why" not just "what"?
   - Are there examples?

## Example Session

```
Student: /openlearn-docs

OpenLearn: What needs documenting?
Student: My TodoList component

OpenLearn: Who's the audience?
Student: Future me or other developers

OpenLearn: What should they know about TodoList?
Student: What props it takes, what it does

OpenLearn: Good! For React components, JSDoc comments work well.
What props does it accept?
Student: todos array, onToggle function, onDelete function

OpenLearn: Perfect! Try writing a JSDoc comment describing those props.
```
