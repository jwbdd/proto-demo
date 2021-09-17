load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Something below here needs skylib but doesn't import it!
http_archive(
    name = "bazel_skylib",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
    ],
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

http_archive(
    name = "rules_cc",
    sha256 = "1e19e9a3bc3d4ee91d7fcad00653485ee6c798efbbf9588d40b34cbfbded143d",
    strip_prefix = "rules_cc-68cb652a71e7e7e2858c50593e5a9e3b94e5b9a9",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/68cb652a71e7e7e2858c50593e5a9e3b94e5b9a9.zip"],
)
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
rules_cc_dependencies()

http_archive(
    name = "com_github_google_benchmark",
    strip_prefix = "benchmark-1.5.6",
    urls = ["https://github.com/google/benchmark/archive/refs/tags/v1.5.6.zip"],
)

# Seems irrelevant, but tcmalloc won't build without this.
http_archive(
    name = "rules_fuzzing",
    sha256 = "127d7c45e9b7520b3c42145b3cb1b8c26477cdaed0521b02a0298907339fefa1",
    strip_prefix = "rules_fuzzing-0.2.0",
    urls = ["https://github.com/bazelbuild/rules_fuzzing/archive/v0.2.0.zip"],
)

load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")

rules_fuzzing_dependencies()

load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")

rules_fuzzing_init()

git_repository(
    name = "com_google_tcmalloc",
    branch = "master",
    recursive_init_submodules = True,
    remote = "https://github.com/google/tcmalloc.git",
)

http_archive(
    name = "rules_proto",
    sha256 = "66bfdf8782796239d3875d37e7de19b1d94301e8972b3cbd2446b332429b4df1",
    strip_prefix = "rules_proto-4.0.0",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "com_github_google_glog",
    sha256 = "21bc744fb7f2fa701ee8db339ded7dce4f975d0d55837a97be7d46e8382dea5a",
    strip_prefix = "glog-0.5.0",
    urls = ["https://github.com/google/glog/archive/v0.5.0.zip"],
)
