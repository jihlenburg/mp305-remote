/* Address: ram:0000384e; name: FUN_ram_0000384e; body bytes: 20 */

void FUN_ram_0000384e(int param_1)

{
  gp = &DAT_ram_20002000;
  decode_transport_byte(&DAT_ram_20003a50 + param_1 * 0x10c);
  return;
}

