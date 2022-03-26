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
import falcon
from .MSAuthCommunication import msa_oauth_token_init, msa_oauth_token_refresh
import requests

class AuthTokenGetter:
    client_id: str = None
    client_sec: str = None
    def __init__(self, client_id: str, client_sec: str):
        self.client_id = client_id
        self.client_sec = client_sec

    def parse_params(self, req: falcon.Request) -> [str, str]:
        auth_code = req.params["code"]
        refresh_token = req.params["refresh_token"]
        client_id = req.params["client_id"]

        if(auth_code and not refresh_token):
            return client_id, auth_code
        elif(refresh_token and not auth_code):
            return client_id, refresh_token
        else:
            # FIXME: Throw error and abort
            return client_id, None

    async def on_post_init(self, req: falcon.Request, resp: falcon.Response) -> None:
        auth_code, client_id = self.parse_params(req)
        xr = msa_oauth_token_init(client_id=client_id, auth_code=auth_code, config_client_id=self.client_id, config_client_secret=self.client_sec)
        resp.status = xr.status_code
        resp.text = xr.text
        return

    async def on_post_refresh(self, req: falcon.Request, resp: falcon.Response) -> None:
        token, client_id = self.parse_params(req)
        xr = msa_oauth_token_refresh(client_id=client_id, refresh_token=token, config_client_id=self.client_id, config_client_secret=self.client_sec)
        resp.status = xr.status_code
        resp.text = xr.text
        return
