/* Address: 0001bf9c; name: FUN_0001bf9c; body bytes: 66 */

undefined4 FUN_0001bf9c(undefined1 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  
  _local_10 = CONCAT13((char)param_2,
                       CONCAT12((char)((uint)param_2 >> 8),
                                CONCAT11((char)((uint)param_2 >> 0x10),param_1)));
  FUN_00015384(2,0x20);
  FUN_00012d10(&local_10,4);
  if ((param_3 != 0) && (param_4 != 0)) {
    FUN_00012d10(param_3,param_4);
  }
  FUN_000153e0(2,0x20);
  return 0;
}

