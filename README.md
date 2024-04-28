# ResilientDB SDK

## Check Python is up-to-date (3.9+)
```sh
python3 --version
```

If your Python version number is too low you may encounter type hinting issues when attempting to run the code. You can use a Python virtual environment, as shown below.

## First-time set up
```sh
sh INSTALL.sh
python3.10 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

The correct Python configuration is needed for transaction validation.

## Running KV service
```sh
# If your virtual environment is not already active:
source venv/bin/activate

# Run the script to start 4 local nodes
sh service/tools/start_kv_service_sdk.sh
```
## Running Crow service (HTTP endpoints)
```sh
bazel build service/http_server/crow_service_main
bazel-bin/service/http_server/crow_service_main service/tools/config/interface/client.config service/http_server/server_config.config
```
For a list of endpoints visit [here](./service/http_server/README.md)

## Testing

```sh
bazel-bin/service/kv_service/kv_service_tools service/tools/config/interface/service.config set test 1234
```
## Running the driver
Examples of using the driver can be seen in [test_driver](/test_driver.py)

Replace the `db_root_url` with the address of the ResilientDB HTTP endpoints e.g. `127.0.0.1:18000`.

## TODO
- Convert the SDK into a package (for pip install)
