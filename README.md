\# AutoCore – Automotive Vehicle Simulation Platform



AutoCore is a modular automotive vehicle simulation platform developed in modern C++.



The project models vehicle subsystems and their interactions through a service-oriented architecture, while providing a Qt6-based interface for vehicle monitoring and control.



\## Features



\- Modular automotive service architecture

\- Engine service

\- Battery service

\- Climate control service

\- Door service

\- Vehicle state management

\- Sensor simulation and monitoring

\- Vehicle health analysis

\- Fault management

\- Centralized service management

\- Service Factory for modular service creation

\- Observer pattern for state/notification handling

\- Multithreaded simulation

\- Mutex-based synchronization

\- SQLite-based data persistence

\- Logging and diagnostics

\- Qt6 graphical dashboard

\- CMake-based build system



\## Architecture



The application is organized around independent vehicle services coordinated by central management components.



```text

&#x20;                   ┌─────────────────────┐

&#x20;                   │     Qt6 Dashboard   │

&#x20;                   └──────────┬──────────┘

&#x20;                              │

&#x20;                   ┌──────────▼──────────┐

&#x20;                   │ Vehicle Controller  │

&#x20;                   └──────────┬──────────┘

&#x20;                              │

&#x20;            ┌─────────────────▼─────────────────┐

&#x20;            │          Service Manager         │

&#x20;            └───────┬─────────┬─────────┬──────┘

&#x20;                    │         │         │

&#x20;               ┌────▼───┐ ┌──▼────┐ ┌──▼──────┐

&#x20;               │ Engine │ │Battery│ │ Climate │

&#x20;               │Service │ │Service│ │ Service │

&#x20;               └────────┘ └───────┘ └─────────┘

&#x20;                    │         │         │

&#x20;                    └─────────┼─────────┘

&#x20;                              │

&#x20;                   ┌──────────▼──────────┐

&#x20;                   │  Vehicle State /    │

&#x20;                   │ Sensor Management   │

&#x20;                   └──────────┬──────────┘

&#x20;                              │

&#x20;                   ┌──────────▼──────────┐

&#x20;                   │ SQLite Persistence  │

&#x20;                   └─────────────────────┘

