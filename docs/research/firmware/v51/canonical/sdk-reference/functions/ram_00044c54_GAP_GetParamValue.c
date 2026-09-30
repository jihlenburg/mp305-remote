/* Address: ram:00044c54; name: GAP_GetParamValue; body bytes: 32 */

undefined2 GAP_GetParamValue(uint param_1)

{
  gp = 0x20004000;
  if (param_1 < 0x40) {
    return (&DAT_ram_20001c24)[param_1];
  }
  return 0xffff;
}

