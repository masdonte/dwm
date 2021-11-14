{ stdenv, fetchurl, libX11, libXft, libXinerama }:

stdenv.mkDerivation {
  name = "dwm-head";

  src = builtins.filterSource
    (path: type: (toString path) != (toString ./.git)) ./.;

  buildInputs = [ libX11 libXft libXinerama ];

  prePatch = ''
    substituteInPlace config.mk --replace '/usr/local' $out
  '';

  meta = with stdenv.lib; {
    description = "Simple Terminal";
    homepage = https://dwm.suckless.org/;
    license = licenses.mit;
    platforms = platforms.all;
  };
}
