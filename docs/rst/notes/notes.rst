.. include:: ../exports/alias.include

.. _release_notes:

###################
Forthcoming Version
###################

.. include:: forthcoming_version.rst

##############
Version v0.2.0
##############

This release includes the following **Configuration features**:

* Support TLS over TCP configuration and communication.
* Support IPv6 communication via UDP, TCP and TLS over TCP.
* Support DNS by given Domain Name in configuration instead of an IP address.
* Support keyed topics.

This release includes the following **Routing features**:

* Zero-Copy data transmission between internal Participants.

This release includes the following **User Interface features**:

* Shutdown the DDS Router application gracefully sending ``SIGTERM`` (``kill``) or ``SIGINT`` (``^C``) signals.

This release includes the following **Continuous-Integration features**:

* Add communication tests for UDP, TCP and TLS over TCP WAN cases.
* Extend tool test with more complex configurations.
* Remove Flaky tests from CI required passing tests.
* Implement a new class to check that no warning or error logs are produced during test executions.
* Add gMock to test libraries.

This release fixes the following **major bugs**:

* Fix GUID creation when explicit guid is provided.
* Show error when participant ids are duplicated.

This release fixes the following **minor bugs**:

* Change ``YAML`` example configurations to ``YAML`` format (instead of ``JSON``) fixing
  an issue when blank lines were missing at the end of the file.
* Normalize the error and process exit when failure.
* Fix documentation typos.

#################
Previous Versions
#################

.. include:: previous_versions/v0.1.0.rst
