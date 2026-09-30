/* Address: ram:00003ed6; name: FUN_ram_00003ed6; body bytes: 74 */

void FUN_ram_00003ed6(char *param_1)

{
  gp = &DAT_ram_20002000;
  if (*param_1 != '\0') {
    if ((param_1[1] == -0x42) && (param_1[2] == -1)) {
      FUN_ram_00001d1a(&DAT_ram_20002f30,0,6);
    }
    FUN_ram_00001d1a(param_1,0,*param_1);
    return;
  }
  return;
}

