project_name = jsoo-css
DUNE = opam exec -- dune
opam_file = $(project_name).opam

.DEFAULT_GOAL := help

.PHONY: help
help: ## Print this help message
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: all
all: ## Install the packages on the system
	$(DUNE) install --root .
	$(DUNE) build --root . @install

.PHONY: create-switch
create-switch:
	opam switch create . 4.12.0 --deps-only --locked --no-install -y

.PHONY: init
init: setupGitHooks pins install ## Configure everything to develop this repository in local

.PHONY: setupGitHooks
setupGitHooks: ## Configure git to point githooks in .githooks folder
	git config core.hooksPath .githooks

.PHONY: pins
pins: ## Pin development dependencies
	opam pin add jsoo-css.dev . --no-action

.PHONY: install
install: all ## Install development dependencies
	opam install --deps-only --with-test --with-doc -y .

.PHONY: deps
deps: $(opam_file) ## Alias to update the opam file and install the needed deps

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

.PHONY: format-check
format-check: ## Checks if format is correct
	$(DUNE) build @fmt

.PHONY: watch
watch: ## Watch for the filesystem and rebuild on every change
	$(DUNE) build --root . --watch

.PHONY: utop
utop: ## Run a REPL and link with the project's libraries
	$(DUNE) utop --root . lib -- -implicit-bindings
