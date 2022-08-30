{
  description = "Binette's build of DWM";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
    in
    {
      overlay = final: prev: {
        dwm = with final; let nix = final.nix; in stdenv.mkDerivation {
          name = "dwm";
          buildInputs = [ libX11 libXft libXinerama ];
          src = builtins.path { path = ./.; name = "dwm"; };
        };
      };
      defaultPackage = system: (import nixpkgs {
        inherit system;
        overlays = [ self.overlay ];
      }).dwm;
    };
}
