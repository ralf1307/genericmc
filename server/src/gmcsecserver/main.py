#!/usr/bin/env python3
"""
    Copyright (C) 2021 Ralf Rachinger
    Copyright (C) 2021 GenericMC Contributors

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    This project is going to be stored on https://sr.ht/~ralf1307/genericmc
    and you can reach me directly by a mail to genericmc@ralfrachinger.de
"""

import falcon.asgi
from .AuthTokenGetter import AuthTokenGetter
from .config import ClientID, ClientSecret 

def main():
    app = falcon.asgi.App()
    atg = AuthTokenGetter(ClientID, ClientSecret)
    app.add_route('/auth/token/init', atg, suffix='init')
    app.add_route('/auth/token/refresh', atg, suffix='refresh')

if __name__ == '__main__':
    main()
