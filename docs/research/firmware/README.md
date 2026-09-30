# Firmware research

The [source narrative](../firmware.md) explains restoration of V51 and the
main host protocol. These focused documents expand particular areas:

| Document | Subject |
|---|---|
| [Architecture](architecture.md) | Images, startup, memory, dispatch and processor roles |
| [Command map](command-map.md) | Handlers and evidence for supported commands |
| [Permissions](permissions.md) | Binding, UI approval, read access, control and accessory paths |
| [RTOS](rtos.md) | Scheduling, tasks, queues, mutexes, semaphores, timers and allocation |
| [Readable reconstruction](readable.md) | Reviewed C equivalents and original-instruction comparisons |
| [Verification](verification.md) | The earlier 2835-case run and links to later recovery checks |
| [V51 evidence](v51/README.md) | Complete analysis exports, preserved Ghidra state and independent comparisons |

To analyze another release, follow the [workflow](../workflow/README.md).
A decompiled function is an analysis result with uncertain boundaries and
types. It is not recovered manufacturer source or a buildable replacement.
