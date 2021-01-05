#!/usr/bin/env bash

main() {

  while [[ "$#" -gt 0 ]]; do
      case $1 in
          -k|--key) key="$2"; shift;;
          -e|--encrypt) encrypt="$2"; shift;;
          -d|--decrypt) decrypt="$2"; shift;;
          *) echo "Unknown parameter passed: $1"; exit 1 ;;
      esac
      shift
  done

  if [[ ! -f key.pem ]]
  then
    generate_rsa_key
  fi

  if [[ ! -f pub.pem ]]
  then
    generate_public_key
  fi

  if [[ $encrypt != "" ]]
  then
      encrypt_data $encrypt
  fi

  if [[ $decrypt != "" ]]
  then
      decrypt_data $decrypt
  fi

}

generate_rsa_key() {
  openssl genrsa -out CPrivateRSA.pem 2048
}

generate_public_key() {
   openssl rsa -in CPrivateRSA.pem -pubout -out CPublic.pem
}

encrypt_data() {
  echo "Start encrypting "$1
  openssl rsautl -encrypt -oaep -inkey CPublic.pem -pubin -in $1 -out secret.bin
}

decrypt_data() {
  echo "Start decrypting "$1
  openssl rsautl -decrypt -oaep -inkey CPrivateRSA.pem -in $1
}

main "$@"