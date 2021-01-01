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
  openssl genrsa -out key.pem 4096
}

generate_public_key() {
   openssl rsa -in key.pem -pubout -out pub.pem
}

encrypt_data() {
  echo "Start encrypting "$1
  openssl rsautl -encrypt -inkey pub.pem -pubin -in $1 -out file.bin
}

decrypt_data() {
  echo "Start decrypting "$1
  openssl rsautl -decrypt -inkey key.pem -in $1
}

main "$@"