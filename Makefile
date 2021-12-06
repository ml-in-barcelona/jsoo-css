.DEFAULT_GOAL := all

DUNE = $(DUNE)

ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

.PHONY: help
help: ## Print this help message
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: all
all:
	$(DUNE) build --root . @install

.PHONY: pin-reason-native
pin-reason-native: ## Install development dependencies
	opam pin add -y jsoo-react https://github.com/reason-in-barcelona/jsoo-react.git
	opam pin add -y pastel https://github.com/reasonml/reason-native.git
	opam pin add -y cli https://github.com/reasonml/reason-native.git
	opam pin add -y file-context-printer https://github.com/reasonml/reason-native.git
	opam pin add -y rely https://github.com/reasonml/reason-native.git

.PHONY: install
install: all ## Install the packages on the system
	$(DUNE) install --root .

.PHONY: create-switch
create-switch:
	opam switch create . 4.12.0 --deps-only --locked

.PHONY: dev
init: pin-reason-native ## Install development dependencies
	git config core.hooksPath .githooks
	opam pin add -y ocaml-lsp-server https://github.com/ocaml/ocaml-lsp.git
	opam install -y dune-release merlin ocaml-lsp-server
	opam install --deps-only --with-test --with-doc -y .

.PHONY: build
build: ## Build the project, including non installable libraries and executables
	$(DUNE) build --root .

.PHONY: start
start: all ## Serve the application with a local HTTP server
	cd demo && yarn start

.PHONY: test
test: ## Run the unit tests
	$(DUNE) build --root . @test/runtest -f

.PHONY: test-wactch
test-watch: ## Run the unit tests in watch mode
	$(DUNE) build --root . @test/runtest --watch

.PHONY: clean
clean: ## Clean build artifacts and other generated files
	$(DUNE) clean --root .

.PHONY: doc
doc: ## Generate odoc documentation
	$(DUNE) build --root . @doc

.PHONY: servedoc
servedoc: doc ## Open odoc documentation with default web browser
	$(BROWSER) _build/default/_doc/_html/index.html

.PHONY: format
format: ## Format the codebase with ocamlformat
	$(DUNE) build --root . --auto-promote @fmt

.PHONY: watch
watch: ## Watch for the filesystem and rebuild on every change
	$(DUNE) build --root . --watch

.PHONY: utop
utop: ## Run a REPL and link with the project's libraries
	$(DUNE) utop --root . lib -- -implicit-bindings
