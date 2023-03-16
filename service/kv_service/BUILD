package(default_visibility = ["//visibility:public"])

cc_library(
    name = "resdb_kv_client",
    srcs = ["resdb_kv_client.cpp"],
    hdrs = ["resdb_kv_client.h"],
    deps = [
        "//service/kv_service/proto:kv_server_cc_proto",
        "@nexres_release//client:resdb_user_client",
    ],
)

cc_library(
    name = "py_verificator",
    srcs = ["py_verificator.cpp"],
    hdrs = ["py_verificator.h"],
    tags = ["manual"],
    deps = [
	"@pybind11",
        "@pybind11//:pybind11_embed",
	"@com_github_google_glog//:glog",
    ],
)

cc_library(
    name = "kv_service_transaction_manager",
    srcs = ["kv_service_transaction_manager.cpp"],
    hdrs = ["kv_service_transaction_manager.h"],
    deps = [
        ":py_verificator",
        "//service/kv_service/proto:kv_server_cc_proto",
	"@nexres_release//common:comm",
        "@nexres_release//config:resdb_config_utils",
        "@nexres_release//durable_layer:leveldb_durable",
        "@nexres_release//durable_layer:rocksdb_durable",
        "@nexres_release//execution:transaction_executor_impl",
    ]
)

cc_binary(
    name = "kv_server",
    srcs = ["kv_server.cpp"],
    deps = [
        ":kv_service_transaction_manager",
	"@nexres_release//application/utils:server_factory",
        "@nexres_release//config:resdb_config_utils",
    ],
)

cc_binary(
    name = "kv_service_tools",
    srcs = ["kv_service_tools.cpp"],
    deps = [
        "@nexres_release//config:resdb_config_utils",
        ":resdb_kv_client",
    ],
)


