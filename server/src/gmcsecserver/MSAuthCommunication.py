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

import requests

# https://wiki.vg/Microsoft_Authentication_Scheme

URL_OAUTH20_TOKEN = 'https://login.live.com/oauth20_token.srf'
HEADERS_OAUTH20_TOKEN = {'Content-Type': 'application/x-www-form-urlencoded'}
#'scope': SCOPE_XLIVE + '%20' + SCOPE_OFFLINEACCESS,
SCOPE_XLIVE = 'XboxLive.signin'
SCOPE_OFFLINEACCESS = 'offline_access'
GRANT_TYPE_AUTH_CODE = 'authorization_code'
GRANT_TYPE_REFRESH_TOKEN = 'refresh_token'

def msa_oauth_token(grant_type: str, auth_code: str = None, client_id: str = '', refresh_token: str = None, config_client_id: str = None, config_client_secret: str = None) -> requests.Response:
    if client_id == config_client_id:
        # Dictionary keys with value None wont get added to the parameters
        req = requests.request(
            method='POST',
            url=URL_OAUTH20_TOKEN,
            headers=HEADERS_OAUTH20_TOKEN,
            params={
                'client_id': config_client_id,
                'client_secret': config_client_secret,
                'code': auth_code,
                'refresh_token': refresh_token,
                'grant_type': grant_type,
                'redirect_uri': 'https://127.0.0.1/',
            }
        )
    if not req.ok:
        #FIXME: Propper logging
        print('MSAuthCommunication: msa_oauth_token: bad request')
    return req

def msa_oauth_token_init(client_id:str, auth_code: str, config_client_id: str, config_client_secret: str) -> requests.Response:
    req = msa_oauth_token(grant_type=GRANT_TYPE_AUTH_CODE, auth_code=auth_code, client_id=client_id, config_client_id=config_client_id, config_client_secret=config_client_secret)
    return req

def msa_oauth_token_refresh(client_id: str, refresh_token: str, config_client_id: str, config_client_secret: str) -> requests.Response:
    req = msa_oauth_token(grant_type=GRANT_TYPE_REFRESH_TOKEN, refresh_token=refresh_token, client_id=client_id, config_client_id=config_client_id, config_client_secret=config_client_secret)
    return req
