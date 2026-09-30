/* Address: ram:00004074; name: queue_gatt_to_main; body bytes: 104 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Copies payload, appends 0x31 for route 0 or zero otherwise, creates type 6 internal frame. */

void queue_gatt_to_main(undefined4 param_1,int param_2,int param_3,undefined4 param_4,
                       undefined4 param_5)

{
  gp = &DAT_ram_20002000;
  if (param_2 != 0) {
    (*_DAT_ram_0004004c)(&DAT_ram_20003a54,param_1,param_2,param_4,param_5,_DAT_ram_0004004c);
    if (param_3 == 0) {
      (&DAT_ram_20003a54)[param_2] = 0x31;
    }
    else {
      (&DAT_ram_20003a54)[param_2] = 0;
    }
    DAT_ram_20003a52 = (short)param_2 + 1;
    DAT_ram_20003a50 = 0x206;
    DAT_ram_20003c58 = 1;
    return;
  }
  return;
}

