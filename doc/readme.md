# nikozdev

- nikodim zimin developer
- expirement-friendly solo-developer
- interested in
> artifical intelligence - one of the most useful domains
> gamedev - the highest
> metadev - simplifying dev process by making libraries, frameworks, a-p-i
- this purpose of this file is for describing myself and the rules i follow

## tools

### version control

- versioning schema
> earlier i tried using my custom conventions with fancy rules
> > it looked like "0xa0a0a0" which is the same as "0.0.0"
> > it was easy to integrate in c programs and store as a hex number
> > but it was useless and inconvenient anyways
> once i started using cmake - i switched to the traditional "m.m.m"
> > major for backwards incompatible changes
> > minor for backwards compatible changes, extensions, features
> > micro for fully compatible changes, fixes, patches
- on local - use git - god instrument to rule them all
- on remote - use own git service and github as a backup
- ignored content
> generated files - always
> resource files - always bigger than 256kb, sometimes bigger than 64kb
- i am gonna stop using submodules
> i am having too many changes in my submodules
> my urls are very inconsistent
> i would preffer taking a bare minimum of dependency repos i need
- i am gonna stop using tags
> my git history is not very stable
> and i can afford "git rebase -i" on my private solo projects
> tags are harder to manage in case of story changes
> branches are more flexible

### source code editing

- neovim is my favorite text editor
> insanely simple nice minimalistic terminal user interface
> great extensibility and configuration
> incredible keyboard-driven interface
> the highest performance-quality ratio
> there is no other editor for now, that allows me to work faster
> i don't wanna go back to vscode

### source code formatting

- clang-format is enough to keep my coding style more consistent
> it usually auto-runs on saving cpp file using [env/clang-format.yaml]

### programming language

- c++ has been my favorite for a long time
> and this is still my main tool
- long ago i decided to stop lerning multiple languages
> to master just one language at a time

## custom standards and conventions

- i prefer following a strict and defined style
> this is my consistency and stability in development

### project file hierarchy

- env - environment
> formatter scripts and configs
> build system scripts and configs
- src - source
> the actual source code included into the project
- gen - generated
> all files generated in the project
> linked binary files
> compiled object code
> build system output
> caches
- rsc - resource
> files
> > audio
> > video
> > image
> > fonts
> rules
> > the contents are usually ignored and excluded from git
- doc - documents
> technical documentation about a library or software
> license
> readme

### naming convention

- 0.0
> pascal case
- 1.0
> minimum word separators
> named units with same concepts have the same name length
> > abbreviations to keep that
> always lowercase
> _snake_case_ everywhere
- 2.0
> capital case represents a distinct separation
> named units with same concepts have the same name length
> > abbreviations to keep that
> > that's why direct hungarian notation is discouraged
> > it is hard to keep various type abbreviations short
> the first character of every name is always
> > lowercase
> > the abbreviation of a name type
like 'n' for namespace or 'v' for variable or 'd' for preprocessor definition
