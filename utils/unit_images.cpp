#include <bits/stdc++.h>
using namespace std;

int main() {
  constexpr int NATS = 16;
  array<string, NATS> nat_arr = {"os", "bm", "ge", "yc", "bh", "rf", "gs", "bd", "ab", "js", "ci", "pc", "tg", "pl", "ar", "wn"};
  constexpr int UNITS = 25;
  array<string, UNITS> uni_arr = {"anti-air", "apc", "artillery", "b-copter", "battleship", "blackboat", "blackbomb", "bomber", "carrier", "cruiser", "fighter", "infantry", "lander", "md.tank", "mech", "megatank", "missile", "neotank", "piperunner", "recon", "rocket", "stealth", "sub", "t-copter", "tank"};

  string link_pre = "https://awbw.amarriner.com/terrain/ani/"; 
  for (int n = 0; n < NATS; n++) {
    for (int u = 0; u < UNITS; u++) {
      string cmd = "wget " + link_pre + nat_arr[n] + uni_arr[u] + ".gif" + " -P ../res/assets/units/";
      system(cmd.c_str());
    }
  }
}
