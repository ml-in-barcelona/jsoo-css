# Contributing

## Setup your development environment

First, you will need to install [npm](https://npmjs.com) to install Javascript dependencies.

In `asset/`:

```
npm install
```

You need Opam, you can install it by following [Opam's documentation](https://opam.ocaml.org/doc/Install.html).

With Opam installed, you can install the dependencies with:

```bash
make dev
```

Then, build the project with:

```bash
make build
```

### Running the app

Building the project will perform the following steps:

- Generate a file `main.js` that will inject our application in the `#root` element of `index.html`.
- Generate a file `main.css` that is required by `index.html`

To run the application, we install `serve` as a dev dependencies. You can run a web server with the content of `asset/static` with:

```sh
cd asset && npm start
```

Or, alternatively, you can use the `make` alias:


```bash
make start
```

### Running Tests

You can run the test compiled executable:


```bash
make test
```

### Building documentation

Documentation for the libraries in the project can be generated with:


```bash
make doc
open-cli $(make doc-path)
```

This assumes you have a command like [open-cli](https://github.com/sindresorhus/open-cli) installed on your system.

> NOTE: On macOS, you can use the system command `open`, for instance `open $(make doc-path)`

### Repository Structure

The following snippet describes demo's repository structure.

```text
.
├── asset/
|   Contains the javascript environment and the static assets.

├── asset/static/
|   Static assets of the application.
│
├── bin/
|   Source for jsoo-css-demo's compiled application. This links to the library defined in `lib/`.
│
├── lib/
|   Source for demo's library. Contains demo's core functionnalities.
│
├── test/
|   Unit tests and integration tests for demo.
│
├── dune-project
|   Dune file used to mark the root of the project and define project-wide parameters.
|   For the documentation of the syntax, see https://dune.readthedocs.io/en/stable/dune-files.html#dune-project
│
├── LICENSE
│
├── Makefile
|   Make file containing common development command.
│
├── README.md
│
└── jsoo-css-demo.opam
    Opam package definition.
    To know more about creating and publishing opam packages, see https://opam.ocaml.org/doc/Packaging.html.
```
