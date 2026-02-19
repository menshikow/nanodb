---
description: Check progress from SQLite database
agent: mentor
---

# /openlearn-status

Check project progress and stats from the database.

## Flow

1. **Read config and roadmap**
   - Read `.opencode/openlearn/config.json`
   - Read `.opencode/openlearn/product/roadmap.md`

2. **Query SQLite database for stats**
   - Total learnings captured
   - Topics encountered
   - Recent activity (30 days)
   - Active objectives
   - Gate scores

3. **Calculate progress**
   - Tasks completed / total
   - Gates passed statistics
   - Learning journey metrics

4. **Show progress dashboard**
   - Visual progress bars
   - Phase progress
   - Current tasks
   - Learning statistics

## Database Queries

### Get learning stats:
```typescript
import { getLearningStats, getGateStats, getTopics } from "./src/db.ts";

const stats = getLearningStats();
// Returns: { totalLearnings, totalTopics, recentLearnings, 
//            activeObjectives, topTopics }

const gateStats = getGateStats();
// Returns: { totalGates, passedGates, averageScore }

const topics = getTopics();
// Returns: Array of topics with encounter counts
```

### SQL equivalents:
```sql
-- Total learnings
SELECT COUNT(*) FROM learnings;

-- Topics encountered
SELECT COUNT(*) FROM topics;

-- Recent learnings (30 days)
SELECT COUNT(*) FROM learnings 
WHERE timestamp > datetime('now', '-30 days');

-- Active objectives
SELECT COUNT(*) FROM objectives WHERE status = 'active';

-- Top topics
SELECT name, count FROM topics ORDER BY count DESC LIMIT 5;

-- Gate pass rate
SELECT 
  COUNT(*) as total,
  SUM(CASE WHEN passed = 1 THEN 1 ELSE 0 END) as passed,
  AVG(score) as avg_score
FROM gate_results;
```

## Example Output

```
📊 OpenLearn Status
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

🎯 Project: Todo App
📍 Current Phase: Phase 1 - Foundation

Phase Progress:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Phase 1: Foundation        ████████░░ 80% (4/5 tasks)
Phase 2: Core Features     ░░░░░░░░░░  0% (0/3 tasks)
Phase 3: Polish            ░░░░░░░░░░  0% (0/2 tasks)

📚 Learning Journey:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Topics encountered: 12
Top topics:
  • React hooks (5x)
  • State management (3x)
  • CSS Grid (2x)

Learnings captured: 8
Recent (30 days): 3

Active objectives: 2

🏆 Gate Statistics:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Total gates run: 16
Passed: 14 (88%)
Average score: 82/100

📝 Current Tasks:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
[x] Set up project
[x] Create TodoItem component
[x] Create TodoList component
[x] Add task functionality
[ ] Persist to localStorage

Next: Complete localStorage persistence

💾 Data Storage:
Database: .opencode/openlearn/openlearn.db
Learnings: .opencode/openlearn/learnings/
```

## Implementation Notes

Visual progress bars can be simple ASCII:
```typescript
function renderProgressBar(percent: number, width: number = 20): string {
  const filled = Math.round((percent / 100) * width);
  const empty = width - filled;
  return "█".repeat(filled) + "░".repeat(empty);
}

// Usage
const progress = renderProgressBar(80);
console.log(`Phase 1: ${progress} 80%`);
// Output: Phase 1: ████████████████░░░░ 80%
```

Color output:
- Green: Success/completed
- Yellow: In progress/warning
- Red: Failed/blocking
- Blue: Information
