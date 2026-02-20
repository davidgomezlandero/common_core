# 🧪 Transcendence Testing Guide

This guide explains how to use the project's automatic validation scripts.

---

## 📋 Available Scripts

### 1. `test_auto.sh` - Subject Module Validation

Validates the **26 modules** specified in `en.subject.pdf`:
- Major modules (1.0 point each)
- Minor modules (0.5 points each)
- Minimum to pass: 7.0 points
- Bonus level: 9.5+ points

**Generates:** `test_result.md`

### 2. `test_evaluation.sh` - Evaluation Criteria Validation

Verifies the **61 criteria** from the official evaluation PDF:
- Preliminary Setup (6 checks)
- Project Overview (6 checks)
- User Management (8 checks)
- Gameplay (7 checks)
- Chat System (5 checks)
- AI Opponent (4 checks)
- Security (7 checks)
- Blockchain (5 checks)
- DevOps (5 checks)
- Bonus Features (8 checks)

**Generates:** `test_evaluation_result.md`

---

## 🚀 Basic Usage

### Preparation (IMPORTANT)

**Before running the scripts, start the containers:**

```bash
make up

# Wait 10-15 seconds for everything to start
sleep 15
```

### Run Validations

```bash
# Option 1: Subject module validation
make test

# Option 2: Evaluation criteria validation
make evaluation

# Option 3: Both complete validations
make test-all
```

### Direct Execution

```bash
# Run scripts directly (also works)
./test_auto.sh
./test_evaluation.sh
```

---

## 🔍 Pre-Flight Checks

Both scripts include **automatic pre-checks**:

### ✅ Checks Performed

1. **Docker daemon active**
   - Verifies that Docker is running
   
2. **Transcendence containers**
   - Detects if the containers are up
   - Counts how many containers are running
   
3. **Critical files**
   - `docker-compose.yml`
   - `Makefile`
   - `backend/` and `frontend/` directories
   
4. **Backend API** (port 3000)
   - Verifies connectivity with the backend
   
5. **Frontend** (port 2323)
   - Verifies that the frontend responds

### ⚠️ Behavior with Warnings

If problems are detected, the script:

1. **Displays the detected warnings**
2. **Provides recommendations** (e.g.: run `make up`)
3. **Asks whether to continue:** `Continue anyway? (y/N)`

**Options:**
- **N (or Enter):** Cancels execution → You must resolve the problem
- **Y:** Continues with warnings → Some tests will fail

---

## 📊 Interpreting Results

### test_auto.sh → test_result.md

```markdown
## 📊 FINAL SCORE

| Category | Modules | Points Obtained |
|----------|---------|-----------------|
| Major Modules | 9 / 15 | 9.0 pts |
| Minor Modules | 6 / 11 | 3.0 pts |
| TOTAL | 15 / 26 | 12.0 / 21.0 pts |
```

**Interpretation:**
- ✅ **>= 9.5 pts:** PASSED WITH BONUS ⭐⭐⭐
- ✅ **>= 7.0 pts:** PASSED ✅
- ⚠️  **5.0-6.9 pts:** CLOSE (implement more modules)
- ❌ **< 5.0 pts:** INSUFFICIENT

### test_evaluation.sh → test_evaluation_result.md

```markdown
## 📊 EXECUTIVE SUMMARY

| Metric | Value |
|--------|-------|
| Criteria evaluated | 61 |
| Criteria passed | ✅ 55 |
| Criteria not met | ❌ 6 |
| Pass percentage | 90.2% |
```

**Interpretation:**
- ✅ **>= 80%:** EXCELLENT ⭐⭐⭐
- ✅ **>= 60%:** PASSED ✅
- ❌ **< 60%:** REQUIRES WORK

---

## 🛠️ Troubleshooting

### Problem: "Containers are NOT running"

**Solution:**
```bash
make up
sleep 15
./test_evaluation.sh
```

### Problem: "Backend/Frontend not responding"

**Verify they are up:**
```bash
docker ps | grep transcendence

# You should see at least:
# - transcendence-backend
# - transcendence-frontend
```

**If not, restart:**
```bash
make down
make up
```

### Problem: "Docker daemon is not running"

**Linux:**
```bash
sudo systemctl start docker
```

**macOS:**
```bash
open -a Docker
```

### Problem: Tests fail but containers are running

**Verify connectivity manually:**
```bash
# Backend
curl http://localhost:3000

# Frontend
curl http://localhost:2323

# If they fail, check logs
make logs
```

---

## 📝 Recommended Evaluation Flow

### Before the Defense

1. **Start services**
   ```bash
   make up
   sleep 15
   ```

2. **Run both validations**
   ```bash
   make test-all
   ```

3. **Review reports**
   ```bash
   cat test_result.md
   cat test_evaluation_result.md
   ```

4. **Check score**
   - Subject modules: >= 7.0 points ✅
   - Evaluation criteria: >= 80% ✅

5. **Identify missing criteria**
   - Look for lines with ❌ in the reports
   - Implement critical features if missing

### During the Evaluation

**Show the evaluator:**
```bash
# 1. Run validations live
make evaluation

# 2. Show the generated report
cat test_evaluation_result.md

# 3. Interactive demos (according to the report checklist)
```

---

## 🎓 Most Common Failing Criteria

### Containers Not Running

- ❌ Backend is running and responding
- ❌ Frontend is running and responding
- ❌ Multiple services in docker-compose

**Fix:** `make up`

### Missing Files

- ❌ Vault AppRole (srcs/secrets/api-approle/)
- ❌ SSL certificates

**Fix:** Run initialization scripts:
```bash
./srcs/scripts/00.gen_selfsigned_cert.sh
./srcs/scripts/01.init_waf_and_vault.sh
```

### Unimplemented Features

- ❌ 2FA/TOTP
- ❌ Responsive design
- ❌ SSR (Server-Side Rendering)

**Note:** These are optional bonuses and do not block passing

---

## 📚 Related Files

- `test_auto.sh` - Module validation script
- `test_evaluation.sh` - Evaluation validation script
- `test_result.md` - Module report (generated)
- `test_evaluation_result.md` - Evaluation report (generated)
- `Makefile` - Make commands to run tests
- `README.md` - Main project documentation

---

## 🤝 Support

If you encounter problems with the scripts:

1. Verify that Docker is running
2. Run `make up` before the tests
3. Check logs: `make logs`
4. Consult this complete guide

**Team:** davigome, jesopan-, nporras-, rdel-olm & sternero  
**Date:** December 2025  
**Project:** ft_transcendence - 42 School