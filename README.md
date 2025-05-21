# Apache ResilientDB Python SDK (Incubating)

<div align="center">

[![Apache License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](LICENSE)
[![Python Versions](https://img.shields.io/badge/python-3.9%2B-blue)](https://github.com/apache/incubator-resilientdb-python-sdk)
[![Documentation](https://img.shields.io/badge/docs-latest-brightgreen.svg)](./docs)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](./CONTRIBUTING.md)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

High-performance blockchain database SDK for Python applications

[Quick Start](#quick-start) •
[Documentation](#documentation) •
[Examples](#examples) •
[Contributing](#contributing) •
[Support](#support)

</div>

> [!NOTE]  
> Apache ResilientDB is an effort undergoing incubation at The Apache Software Foundation (ASF), sponsored by the Apache Incubator. Incubation is required of all newly accepted projects until a further review indicates that the infrastructure, communications, and decision making process have stabilized in a manner consistent with other successful ASF projects.

## 🚀 Quick Start

### Installation

```bash
# Clone the repository
git clone https://github.com/apache/incubator-resilientdb-python-sdk.git
cd incubator-resilientdb-python-sdk

# Set up the environment
sh INSTALL.sh
python3.10 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

### Basic Usage

```python
from resdb_driver import Resdb
from resdb_driver.crypto import generate_keypair
from typing import Dict, Any

# Initialize the client
db = Resdb('http://127.0.0.1:18000')

# Generate keypairs for the example
alice, bob = generate_keypair(), generate_keypair()

# Create a digital asset
asset = {
    "data": {
        "token_for": "example",
        "description": "Example token",
    },
}

# Prepare transaction
prepared_tx = db.transactions.prepare(
    operation='CREATE',
    signers=alice.public_key,
    recipients=[([bob.public_key], 10)],  # Transfer 10 tokens to Bob
    asset=asset,
)

# Sign the transaction
fulfilled_tx = db.transactions.fulfill(
    prepared_tx, 
    private_keys=alice.private_key
)

# Send the transaction
tx_id_str = db.transactions.send_commit(fulfilled_tx)


# Retrieve the transaction
result = db.transactions.retrieve(fulfilled_tx["id"])
print(f"Retrieved transaction: {result}")
```

## 🌟 Features

- **Transaction Management**
  - Create and send transactions with digital signatures
  - Retrieve and query transaction details
  - Asset-based transaction querying

- **Block Operations**
  - Retrieve blocks by transaction
  - Query block ranges
  - Real-time block updates

- **Asset & Metadata Management**
  - Asset search and retrieval
  - Metadata management
  - Output tracking

- **DB Connection**
  - Automatic failover
  - Round-robin load balancing
  - Connection pooling
  - Exponential backoff

## 📋 Requirements

- Python 3.9 or higher
- Bazel build system
- Debian based linux distros e.g. Ubuntu
- Virtual environment (recommended)

## 🔧 Setup & Configuration

### 1. Start the Key-Value Service

```bash
source venv/bin/activate
sh service/tools/start_kv_service_sdk.sh
```

### 2. Start the HTTP Service

```bash
bazel build service/http_server/crow_service_main
bazel-bin/service/http_server/crow_service_main \\
    service/tools/config/interface/client.config \\
    service/http_server/server_config.config
```

## 📚 Documentation

- [Complete API Reference](./docs/api_reference.md)
- [HTTP Endpoints Guide](./service/http_server/README.md)
- [Contributing Guidelines](./CONTRIBUTING.md)
- [Example Use Cases](./test_driver_2.py)

## 🏗️ Project Structure

```
resilientdb-python-sdk/
├── docs/               # Documentation and guides
├── resdb_driver/      # Core SDK implementation
├── service/           # Service implementations
│   ├── http_server/   # HTTP API service (Crow)
│   └── kv_service/    # Key-Value service
└── test/              # Test suite
```

## 🧪 Testing
TODO: add tests

## 🔍 Troubleshooting

### Common Issues

1. **Connection Refused**
   ```
   Solution: Ensure the HTTP service is running on port 18000
   ```

2. **Python Version Mismatch**
   ```
   Solution: Use Python 3.9 or higher, preferably in a virtual environment
   ```

3. **Bazel Build Failures**
   ```
   Solution: Check Bazel version and ensure all dependencies are installed
   ```

## 🤝 Contributing

We welcome contributions! See our [Contributing Guidelines](./CONTRIBUTING.md) for:
- How to submit patches
- Development workflow
- Coding standards

## 📄 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 💬 Support

- [GitHub Issues](https://github.com/apache/incubator-resilientdb-python-sdk/issues)
- [Mailing Lists](https://lists.apache.org/list.html?dev@resilientdb.apache.org)

## 🗺️ Roadmap

### Current Goals
- [ ] Setting up linting (using [black](https://github.com/psf/black))
- [ ] Convert to pip-installable package
- [ ] Docker setup for local ResilientDB

### Connection Improvements
- [ ] WebSocket support for real-time updates
- [ ] Connection pooling optimization
- [ ] Automatic node health checking
- [ ] Custom retry strategies
- [ ] Connection encryption options
- [ ] Bulk operations support
- [ ] Load balancing strategies
- [ ] Metrics and monitoring

### API Enhancements
- [ ] Add async/await support using aiohttp
- [ ] Complete implementation of async/sync transaction modes
- [ ] Add batch transaction support
- [ ] Implement streaming responses for large datasets
- [ ] Add support for complex query operations
- [ ] Implement automatic request compression
- [ ] Improve transaction ID handling
- [ ] Add retry mechanisms for failed transactions