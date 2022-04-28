#!/bin/bash

PROJECT_NAME="calc"
PACK_DIR="./$PROJECT_NAME"
BIN="$PACK_DIR/usr/local/bin"
OPT="$PACK_DIR/opt/calc"
DEBIAN="$PACK_DIR/DEBIAN"
BUILD="../build"
ASSETS="../assets"

mkdir -p "$BIN" && cp "$BUILD/calc" "$BIN" && mkdir -p "$DEBIAN" && mkdir -p "$OPT" && cp "$ASSETS/icon/icon-full-size.png" "$OPT/calc.png"

mkdir -p "$PACK_DIR/usr/share/applications/"
cp "./control" "$DEBIAN/control"

chmod 0755 "$DEBIAN/control"

dpkg-deb --build --root-owner-group "$PACK_DIR"