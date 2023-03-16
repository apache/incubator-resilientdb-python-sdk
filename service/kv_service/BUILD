package(default_visibility = ["//visibility:public"])

cc_library(
    name = "resdb_kv_client",
    srcs = ["resdb_kv_client.cpp"],
    hdrs = ["resdb_kv_client.h"],
    deps = [
        "@nexres_v2//platform/interface:resdb_transaction_proposer",
        "//service/kv_service/proto:kv_server_cc_proto",
    ],
)

cc_library(
    name = "py_verificator",
    srcs = ["py_verificator.cpp"],
    hdrs = ["py_verificator.h"],
    tags = ["manual"],
    deps = [
        "@nexres_v2//common:comm",
        "@nexres_v2//common:pybind",
    ],
)

cc_library(
    name = "kv_service_transaction_manager",
    srcs = ["kv_service_transaction_manager.cpp"],
    hdrs = ["kv_service_transaction_manager.h"],
    deps = [
        ":py_verificator",
        "@nexres_v2//common:comm",
        "@nexres_v2//platform/config:resdb_config_utils",
        "@nexres_v2//platform/consensus/execution:transaction_manager",
        "@nexres_v2//storage:in_mem_kv_storage",
        "//service/kv_service/proto:kv_server_cc_proto",
    ]
)

cc_binary(
    name = "kv_server",
    srcs = ["kv_server.cpp"],
    deps = [
        ":kv_service_transaction_manager",
        "@nexres_v2//platform/config:resdb_config_utils",
        "@nexres_v2//service/utils:server_factory",
    ],
)

cc_binary(
    name = "kv_service_tools",
    srcs = ["kv_service_tools.cpp"],
    deps = [
        "@nexres_v2//common/proto:signature_info_cc_proto",
        "@nexres_v2//platform/config:resdb_config_utils",
        "//service/kv_service:resdb_kv_client",
    ],
)


