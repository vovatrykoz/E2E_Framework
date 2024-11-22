
/**
 * @namespace e2e
 * @brief The primary namespace of this framework.
 *
 * The `e2e` namespace encompasses:
 * - Task reading and generation.
 * - Reading and managing task instances.
 * - Analytical tools for evaluating timed path reachability.
 * - End-to-end delay calculations.
 *
 * It serves as the core of the framework, providing functionality to model and
 * analyze complex systems efficiently.
 */
namespace e2e {}

/**
 * @namespace e2e::analysis
 * @brief Namespace providing tools for path filtering and delay analysis.
 *
 * The `analysis` namespace offers functionalities for analyzing sets of
 * `TimedPath` objects. It includes methods for:
 * - Filtering unreachable paths based on reachability conditions.
 * - Removing paths that produce duplicate values due to identical start times.
 * - Identifying the path with the maximum end-to-end latency.
 * - Calculating overarching delays using various timing semantics.
 * - Determining predecessor paths based on activation time and path period.
 *
 * This namespace serves as a key component for path-based analysis in the
 * framework, enabling precise evaluation and optimization of timing and
 * reachability.
 */
namespace analysis {}

/**
 * @namespace e2e::mathframework
 * @brief Namespace providing mathematical and logical functions for task instance analysis.
 *
 * The `mathframework` namespace contains critical functions for evaluating the relationships
 * and interactions between task instances in a system. These functions are integral to determining:
 * - Activation time travel (whether a reader task activates before a writer).
 * - Overlap in execution between writer and reader tasks.
 * - Wait conditions based on task priorities during overlapping execution.
 * - Forward reachability between tasks, accounting for time travel and criticality.
 * - Detection of overwrites between writer task instances for the same reader task.
 * - Reachability of an entire timed path of task instances.
 *
 * These utilities form the foundation for analyzing temporal and logical properties of task sets,
 * enabling precise evaluation of scheduling and timing in complex systems.
 */
namespace mathframework {}

/**
 * @namespace e2e::setup
 * @brief Namespace for initialization and setup utilities.
 *
 * The `setup` namespace provides tools for configuring and initializing various components
 * of the framework. It includes functionalities to:
 * - Map string representations to supported logger and reader types.
 * - Create logger and reader objects from enumerated types or string representations.
 * - Manage different logging and task reading implementations for flexible framework usage.
 *
 * The namespace facilitates streamlined configuration by abstracting the creation and setup
 * of loggers (`ILogger`) and readers (`ITaskReader` and `ITaskInstanceReader`).
 */
namespace setup {}

/**
 * @namespace e2e::scheduling
 * @brief Namespace for task and path scheduling utilities.
 *
 * The `scheduling` namespace provides essential tools for analyzing and managing
 * task scheduling in end-to-end paths. It offers functions to:
 * - Calculate properties such as the least common multiple (LCM) for task chains.
 * - Generate task instances from tasks in an end-to-end path.
 * - Construct timed paths based on task instances and their dependencies.
 * - Perform operations like Cartesian product to build complex path combinations.
 *
 * This namespace is crucial for tasks related to time-based path construction,
 * enabling efficient and accurate scheduling analysis.
 */
namespace scheduling {}

/**
 * @namespace e2e::io
 * @brief Input/output utilities for task and path handling.
 *
 * The `io` namespace provides abstractions and implementations for:
 * - Logging results and path analysis outputs.
 * - Reading task chains, instances, and paths from various input sources.
 *
 * This namespace defines core interfaces (`ILogger`, `ITaskReader`, `ITaskInstanceReader`)
 * for extensible input and output functionality, along with example concrete
 * implementations such as `SimplifiedConsoleLogger` and `TaskInstanceInputReader`.
 */
namespace io {}
