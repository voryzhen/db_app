tests_data = [

[
    "Simple 'Insert' and 'Select'",
    "insert 1 user user@main.com\nselect\n.exit\n",
    "db > Executed.\ndb > (1, user, user@main.com)\nExecuted.\ndb > Executed.\n"
],
[
    "Max username 'Insert'",
    "insert 1 useruseruseruseruseruseruseruser user@main.com\nselect\n.exit\n",
    "db > Executed.\ndb > (1, useruseruseruseruseruseruseruser, user@main.com)\nExecuted.\ndb > Executed.\n"
],
[
    "Long string",
    "insert 1 useruseruseruseruseruseruseruser12 user@main.com\nselect\n.exit\n",
    "db > String is too long.\ndb > Executed.\ndb > Executed.\n"
],
[
    "Negative ID",
    "insert -1 user user@main.com\nselect\n.exit\n",
    "db > ID must be positive.\ndb > Executed.\ndb > Executed.\n"
]

]
