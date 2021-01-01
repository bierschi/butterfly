#!/usr/bin/env bash

openssl rsa -in id_rsa.pem -RSAPublicKey_in -pubout > id_pub.pem