project('launcher', 'java')

src = [
    'org/multimc/EntryPoint.java',
    'org/multimc/Launcher.java',
    'org/multimc/LegacyFrame.java',
    'org/multimc/NotFoundException.java',
    'org/multimc/ParamBucket.java',
    'org/multimc/ParseException.java',
    'org/multimc/Utils.java',
    'org/multimc/onesix/OneSixLauncher.java',
    'net/minecraft/Launcher.java',
]

myjar = jar('NewLaunch', src,
main_class: 'org.multimc.EntryPoint'
)

launcher_dep = declare_dependency(sources: myjar)
