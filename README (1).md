# 🚗 THE UNSTOPPABLE SYSTEM  
## QNX Based Fault-Tolerant ADAS Architecture

> *A deterministic, self-recovering automotive safety system built on QNX RTOS using process isolation, CPU core partitioning, watchdog supervision, redundancy, and fail-safe recovery.*

---

# 📌 Project Overview

Modern autonomous and ADAS systems cannot afford downtime.

If a critical perception service crashes:
- the vehicle should **not stop functioning**
- steering and braking must remain deterministic
- backup systems must immediately take over
- recovery should happen automatically

This project demonstrates exactly that.

The Unstoppable System is a **pure QNX RTOS based fault-tolerant architecture** that simulates how real automotive systems maintain safety even during software failures.

The system continuously:
- monitors processes
- detects failures
- restarts crashed applications
- switches to redundant backup systems
- isolates critical and non-critical workloads
- logs all important events
- enters fail-safe mode when redundancy is lost

---

# 🎯 Problem Statement

In safety-critical systems like:
- Autonomous Vehicles
- ADAS Platforms
- Aerospace Controllers
- Railway Safety Systems

a single process failure should never bring down the complete system.

This project solves that problem by implementing:
- watchdog supervision
- redundant backup execution
- deterministic CPU partitioning
- automatic fault recovery
- fail-safe operation

---

# 🧠 Core Idea

The architecture separates the system into:
- **Critical services**
- **Redundant backup services**
- **Non-critical services**
- **Monitoring & recovery services**

Each process runs on a dedicated CPU core using QNX CPU affinity.

If a critical process fails:
1. The watchdog detects failure
2. Recovery manager attempts restart
3. If restart repeatedly fails:
   - backup system becomes active
4. If both systems fail:
   - fail-safe mode activates

The system never stops supervising itself.

---

# 🏗️ System Architecture

| Core | Process | Purpose |
|---|---|---|
| CORE 0 | `controller_app` | Safe steering/braking controller |
| CORE 1 | `primary_app` | Primary LiDAR/Perception |
| CORE 2 | `ghost_app` | Redundant backup perception |
| CORE 2 | `guardian_app` | Predictive monitoring |
| CORE 2 | `monitor_process` | Watchdog + recovery manager |
| CORE 3 | `media_app` | Non-critical infotainment |

---

# ⚙️ Main Components

## 🔹 monitor_process

The brain of the system.

Acts as:
- Watchdog Supervisor
- Arbitration Manager
- Recovery Manager
- Blackbox Logger

Responsibilities:
- start all processes
- monitor health
- restart failed processes
- activate redundancy
- maintain system state
- trigger fail-safe mode

---

## 🔹 primary_app

Simulates:
- primary LiDAR/camera perception

Runs on:
- dedicated critical core

If this process fails:
- recovery begins immediately

---

## 🔹 ghost_app

Redundant backup perception pipeline.

Purpose:
- take over when primary perception becomes unstable

This simulates:
- automotive ECU redundancy

---

## 🔹 controller_app

Represents:
- steering controller
- braking controller
- safe path logic

Runs independently on:
- isolated critical core

This guarantees:
- deterministic timing

---

## 🔹 media_app

Represents:
- infotainment
- UI
- media services

Runs on:
- non-critical core

Its failure never affects:
- controller
- perception
- recovery logic

---

## 🔹 guardian_app

Predictive monitoring service.

Detects:
- latency instability
- overload conditions
- deadline risks

Logs warnings into:

```bash
/tmp/blackbox.log
```

---

## 🔹 Blackbox Logger

All important events are permanently recorded.

Example logs:

```txt
system initialized
media failure
primary failure
primary recovered
ghost active
fail safe mode
latency warning
```

This simulates:
- automotive event data recorders

---

# 🔄 System Workflow

## ✅ NORMAL OPERATION

Initial state:
- primary perception active
- ghost backup standby
- controller deterministic
- media isolated

Monitor continuously checks process health.

---

## ⚠️ NON-CRITICAL FAILURE

Example:

```bash
slay media_app
```

System response:
- watchdog detects failure
- media restarts automatically
- critical systems continue unaffected

---

## 🚨 PRIMARY FAILURE

Example:

```bash
slay primary_app
```

System response:
1. failure detected
2. restart attempted
3. recovery validated
4. system returns to normal

---

## 🔁 REDUNDANT OPERATION

If primary repeatedly fails:
- system promotes `ghost_app`
- ghost becomes ACTIVE perception
- controller switches safely
- operation continues without interruption

---

## 🛑 FAIL SAFE MODE

If both:
- `primary_app`
- `ghost_app`

become unavailable:

System enters:

```txt
FAIL_SAFE_MODE
```

Vehicle transitions into:
- minimum risk state
- safe degraded operation

---

# ⚡ Real-Time Optimizations

The system was optimized for low recovery latency.

### Before Optimization

| Operation | Delay |
|---|---|
| Detection | 2 sec |
| Restart | 2 sec |
| Total Recovery | ~4 sec |

### After Optimization

| Operation | Delay |
|---|---|
| Detection | 100 ms |
| Restart | 100 ms |
| Recovery | ~200–300 ms |

This significantly improves:
- responsiveness
- determinism
- safety behavior

---

# 🔧 Technologies Used

| Technology | Purpose |
|---|---|
| QNX Neutrino RTOS | Real-time operating system |
| C Programming | System implementation |
| QNX ThreadCtl | CPU affinity |
| spawnlp() | Process creation |
| waitpid() | Process monitoring |
| POSIX APIs | Scheduling & timing |

---

# 🚀 Build Instructions

## Compile

```bash
make clean
make
```

## Copy Executables

```bash
cp monitor_process /tmp/
cp primary_app /tmp/
cp ghost_app /tmp/
cp media_app /tmp/
cp guardian_app /tmp/
cp controller_app /tmp/
```

## Run System

```bash
cd /tmp
./monitor_process
```

---

# 🧪 Testing Failures

## Kill Non-Critical Service

```bash
slay media_app
```

Expected:
- automatic restart

---

## Kill Primary Service

```bash
slay primary_app
```

Expected:
- watchdog recovery
- redundancy activation if needed

---

## Stress Non-Critical Core

```bash
./noncritical_core_hog
```

Expected:
- controller remains stable

---

## Stress Critical Core

```bash
./critical_core_hog
```

Expected:
- guardian warnings
- recovery activity

---

# 📊 Key Features

✅ CPU Core Isolation  
✅ Deterministic Scheduling  
✅ Automatic Process Recovery  
✅ Watchdog Supervision  
✅ Redundant Backup Activation  
✅ Predictive Monitoring  
✅ Fail Safe Protection  
✅ Blackbox Event Logging  
✅ Real-Time Optimized Recovery  
✅ QNX Native Implementation  

---

# 🏆 Why This Project Matters

This project demonstrates concepts used in:
- autonomous vehicles
- aircraft control systems
- railway safety systems
- industrial robotics
- medical devices

It is not just a restart mechanism.

It is a complete:
- fault-tolerant supervisory architecture

designed around:
- reliability
- isolation
- deterministic recovery
- continuous operation

---

# 🔮 Future Improvements

Possible enhancements:
- heartbeat IPC monitoring
- QNX pulses/message passing
- distributed redundancy
- health scoring
- adaptive recovery policies
- live telemetry dashboard
- hypervisor integration
- ASIL-oriented safety policies

---

# 👨‍💻 Team Vision

> “A safety-critical system should never completely stop because one software component failed.”

The Unstoppable System was built with the vision of creating:
- resilient
- deterministic
- continuously recoverable

real-time architectures for next-generation autonomous systems.
