#########
Projects
#########


Layouting
---------

To support a dynamic and incremental layout calculation we need to:

Identify affected partitions
Identify affected queries
Layout sub-partitions accordingly
Implement performance improvements of 2 orders of magnitude for wide enterprise tables
The goal is to quickly adapt the physical table layout to a changed workload, without blocking system resources by too frequent changes. The change manager needs to identify if it is viable to perform a transition from one layout to another. HYRISE implements a regret-based amortization process. The change manager is triggered each epoch (a distinct period of time) and calculates if the workload changed and if the accumulated regret is large enough to trigger a layout change. In addition to accumulating over previous epochs, we increase the weight during each epoch that a new layout was better. The transition from one layout to another performs a costly reorganization operation. So the challenge is to redesign and enhance the re-compression process in HYRISE to perform arbitrary column transformations.