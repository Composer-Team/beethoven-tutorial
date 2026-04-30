package vector_add

import beethoven._

// Platform and build-mode are now sourced from Beethoven.toml — see
// `[platform] target` and `[platform] build-mode`. The framework picks up
// this AcceleratorConfig subclass via classpath autodiscovery (driven by
// beethoven.cli.Run, which is the build.sbt mainClass).

class VectorAddConfig extends AcceleratorConfig(
  List(AcceleratorSystemConfig(
    nCores = 3,
    name = "myVectorAdd",
    moduleConstructor = ModuleBuilder(p => new VectorAddCore()(p)),
    memoryChannelConfig = List(
      ReadChannelConfig("vec_a", dataBytes = 4),
      ReadChannelConfig("vec_b", dataBytes = 4),
      WriteChannelConfig("vec_out", dataBytes = 4)
    )
  )))
