load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
        name = "demo_proto",
        srcs = ["demo.proto",],
        )

cc_proto_library(
        name = "demo_cc_proto",
        deps = [":demo_proto",],
        )

cc_test(
        name = "demo",
        srcs = ["demo.cc",],
        deps = [":demo_cc_proto",
                "@com_github_google_benchmark//:benchmark",
                "@com_github_google_glog//:glog",
                ],
        malloc = "@com_google_tcmalloc//tcmalloc",
        )
