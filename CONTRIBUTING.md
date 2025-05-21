# Contributing to Apache ResilientDB Python SDK

We love your input! We want to make contributing to Apache ResilientDB Python SDK as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## Development Process

We use GitHub to host code, to track issues and feature requests, as well as accept pull requests.

1. Fork the repo and create your branch from `main`.
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Ensure the test suite passes.
5. Make sure your code follows the project's coding standards.
6. Issue that pull request!

## Development Setup

1. Clone your fork:
   ```bash
   git clone https://github.com/YOUR_USERNAME/incubator-resilientdb-python-sdk.git
   cd incubator-resilientdb-python-sdk
   ```

2. Set up development environment:
   ```bash
   sh INSTALL.sh
   python3.10 -m venv venv
   source venv/bin/activate
   pip install -r requirements.txt
   ```

3. Create a branch:
   ```bash
   git checkout -b your-feature-name
   ```

## Coding Standards

- Follow PEP 8 style guide for Python code
- Use type hints for function parameters and return values
- Write docstrings for all public methods and classes
- Keep functions focused and concise
- Add comments for complex logic
- Include unit tests for new functionality

## Pull Request Process

1. Update the README.md with details of changes to the interface, if applicable.
2. Update the documentation with details of any new functionality.
3. The PR will be merged once you have the sign-off of at least one maintainer.


## Issue Reporting Guidelines


### Bug Reports

When filing an issue, make sure to answer these questions:

1. What version of Python are you using?
2. What operating system are you using?
3. What did you do?
4. What did you expect to see?
5. What did you see instead?

### Feature Requests

We welcome feature requests! When submitting a feature request, please:

1. Explain the problem you're trying to solve
2. Describe the solution you'd like to see
3. Provide context about alternative solutions you've considered

## Community

- Subscribe to our [mailing lists](https://lists.apache.org/list.html?dev@resilientdb.apache.org)
- Join our discussions on [GitHub Issues](https://github.com/apache/incubator-resilientdb-python-sdk/issues)

## License

By contributing, you agree that your contributions will be licensed under the Apache License, Version 2.0.