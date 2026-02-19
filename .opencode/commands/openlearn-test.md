---
description: Guidance on writing tests
agent: mentor
---

# /openlearn-test

Get guidance on writing tests.

## Flow

1. **Ask what needs testing**
   - What component/function are you testing?
   - What behavior should it have?

2. **Discuss testing strategy**
   - What type of tests? (unit, integration, e2e)
   - What scenarios to cover?
   - What are the edge cases?

3. **Guide through writing tests**
   - Explain testing patterns
   - Show small examples (max 8 lines)
   - Student writes the actual tests

4. **Review test quality**
   - Are tests readable?
   - Do they test the right things?
   - Are they independent?

## Example Session

```
Student: /openlearn-test

OpenLearn: What needs testing?
Student: My TodoItem component

OpenLearn: What should it do?
Student: Show task text, toggle checkbox, call onDelete

OpenLearn: What testing library are you using?
Student: React Testing Library

OpenLearn: Good choice! What's the first thing you want to test?
Student: That it renders the task text

OpenLearn: Exactly! Start with the happy path. How would you test that?
Student: render the component and check if text is in document?

OpenLearn: Perfect! Try writing it.

[Student writes test]

OpenLearn: Looks good! What edge case should we test?
Student: Maybe that clicking checkbox calls onToggle?

OpenLearn: Excellent thinking! That's an interaction test.
```
