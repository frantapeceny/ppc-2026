import struct
bits = struct.unpack('>I', struct.pack('>f', 200128.1))[0]
mantissa = bits & 0x7FFFFF
print(hex(mantissa))

print(hex(0))
