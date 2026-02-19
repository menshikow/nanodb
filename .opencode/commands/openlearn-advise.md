---
description: Query past learnings from SQLite before starting
agent: mentor
---

# /openlearn-advise

Get advice based on past learnings before starting a task.

## Flow

1. **Read past learnings from SQLite**
   - Query `.opencode/openlearn/openlearn.db`
   - Parse learnings table
   - Search for relevant topics

2. **Identify relevant learnings**
   - Match current context with past topics
   - Find related mistakes and insights
   - Sort by relevance and recency

3. **Present advice**
   - Show: "When you worked on [similar task], you learned..."
   - Quote the key insight
   - Ask: "How might this apply here?"

## Database Queries

### Search by topic:
```sql
SELECT * FROM learnings 
WHERE LOWER(topic) = LOWER(?)
ORDER BY timestamp DESC
LIMIT 5
```

### Search by keyword:
```sql
SELECT * FROM learnings 
WHERE LOWER(task) LIKE ? 
   OR LOWER(what_learned) LIKE ?
ORDER BY timestamp DESC
```

### Get top topics:
```sql
SELECT name, count FROM topics 
ORDER BY count DESC 
LIMIT 10
```

## Example Session

```
Student: /openlearn-advise

OpenLearn: What are you about to work on?
Student: Adding a form to edit todos

OpenLearn: [Querying database for relevant learnings...]

💡 Based on your past learnings:

When you built the todo app (2026-02-17), you learned:
> "Lift state to the common parent component. 
> Don't duplicate state in child components."

You also learned about form handling:
> "Controlled components need value + onChange handler."

How might these apply to your edit form feature?

Student: I should probably put the form state in the parent
instead of the form component?

OpenLearn: Exactly! That's the pattern you discovered before.
Also, remember to handle the controlled input pattern.

💡 Related learnings found: 2
💡 Topics to review: React forms, State management
```

## Implementation Notes

Use the database module:
```typescript
import { searchLearnings, getLearningsByTopic, getTopics } from "./src/db.ts";

// Search for relevant learnings
const keyword = "forms";
const relevantLearnings = searchLearnings(keyword);

// Get learnings by specific topic
const topicLearnings = getLearningsByTopic("React Hooks");

// Show frequently encountered topics
const topTopics = getTopics().slice(0, 5);
```

## No Learnings Yet?

If the database is empty:
```
OpenLearn: No previous learnings found in your database yet.

That's normal when starting out! After you complete a few tasks,
use /openlearn-retro to capture what you've learned.

Then /openlearn-advise will help you recall and apply those insights.
```
