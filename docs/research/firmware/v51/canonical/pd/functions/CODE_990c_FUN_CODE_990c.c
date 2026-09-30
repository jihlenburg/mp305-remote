/* Address: CODE:990c; name: FUN_CODE_990c; body bytes: 24 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

undefined1 FUN_CODE_990c(byte param_1,char param_2,byte param_3)

{
  FUN_CODE_33d6();
  return *(undefined1 *)
          CONCAT11((param_2 - (((0xcb < param_1) << 7) >> 7)) -
                   ((CARRY1(param_1 + 0x34,param_3) << 7) >> 7),param_1 + 0x34 + param_3);
}

