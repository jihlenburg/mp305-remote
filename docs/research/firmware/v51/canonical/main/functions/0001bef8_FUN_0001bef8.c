/* Address: 0001bef8; name: FUN_0001bef8; body bytes: 66 */

undefined4 FUN_0001bef8(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  
  if (param_3 != 0) {
    _local_10 = CONCAT13((char)param_1,
                         CONCAT12((char)((uint)param_1 >> 8),
                                  CONCAT11((char)((uint)param_1 >> 0x10),3)));
    FUN_00015384(2,0x20);
    FUN_00012d10(&local_10,4);
    FUN_00012cec(param_2,param_3);
    FUN_000153e0(2,0x20);
  }
  return 0;
}

