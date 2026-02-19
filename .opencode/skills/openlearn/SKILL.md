# OpenLearn Skill

## Description

An AI-mentored development framework for opencode that transforms code-generation into a teaching experience. Junior developers write all the code while receiving Socratic guidance, quality gates, and Context7-powered documentation lookups.

## Installation

```bash
# Copy to your project's .opencode directory
cp -r openlearn/ .opencode/

# Or use opencode skill system (when published)
opencode skill add openlearn
```

## Quick Start

1. **Initialize**: `/openlearn-init`
2. **Plan feature**: `/openlearn-feature`
3. **Get guidance**: `/openlearn-guide`
4. **Complete**: `/openlearn-done`

## Commands

- `/openlearn-init` - Initialize project
- `/openlearn-feature` - Create feature specs
- `/openlearn-guide` - Get implementation guidance
- `/openlearn-stuck` - Debug systematically
- `/openlearn-test` - Test guidance
- `/openlearn-docs` - Documentation help
- `/openlearn-done` - Complete with gates
- `/openlearn-retro` - Capture learnings
- `/openlearn-status` - Check progress
- `/openlearn-profile` - View settings

## Agents

- `@mentor` - Primary teaching agent
- `@ownership-gate` - Understanding verification (BLOCKING)
- `@security-gate` - Security review (BLOCKING)
- `@error-gate` - Error handling review
- `@performance-gate` - Performance analysis
- `@fundamentals-gate` - Code quality
- `@testing-gate` - Test coverage

## Version

1.0.0
