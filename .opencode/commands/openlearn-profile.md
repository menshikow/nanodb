---
description: View/change settings
agent: mentor
---

# /openlearn-profile

View and update OpenLearn settings.

## Flow

1. **Show current profile**
   - Read `.opencode/openlearn/config.json`
   - Display all settings

2. **Ask what to change**
   - Context7 mode (auto/suggest/manual)
   - Analogies preference
   - Background level

3. **Update config**
   - Edit config.json with new values

## Example Session

```
Student: /openlearn-profile

📋 Current Profile:

Background: Coding basics
Analogies: Disabled
Context7 Mode: Auto

What would you like to change?
1. Context7 mode
2. Analogies preference
3. Nothing

Student: 1

New mode:
1. Auto - Always check docs
2. Suggest - Ask before checking
3. Manual - Only when requested

Student: 2

✅ Updated! Context7 mode is now "suggest"
```
