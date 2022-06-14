class NexresException(Exception):
    """Base exception for all nexres exceptions."""


class TransportError(NexresException):
    """Base exception for transport related errors.

    This is mainly for cases where the status code denotes an HTTP error, and
    for cases in which there was a connection error.

    """

    @property
    def status_code(self):
        return self.args[0]

    @property
    def error(self):
        return self.args[1]

    @property
    def info(self):
        return self.args[2]

    @property
    def url(self):
        return self.args[3]


class BadRequest(TransportError):
    """Exception for HTTP 400 errors."""


class NotFoundError(TransportError):
    """Exception for HTTP 404 errors."""


class ServiceUnavailable(TransportError):
    """Exception for HTTP 503 errors."""


class GatewayTimeout(TransportError):
    """Exception for HTTP 503 errors."""


class TimeoutError(NexresException):
    """Raised if the request algorithm times out."""

    @property
    def connection_errors(self):
        """Returns connection errors occurred before timeout expired."""
        return self.args[0]


HTTP_EXCEPTIONS = {
    400: BadRequest,
    404: NotFoundError,
    503: ServiceUnavailable,
    504: GatewayTimeout,
}
