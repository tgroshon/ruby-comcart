require "cargo/version"
require "ffi"

module Comcart
  extend FFI::Library
  ffi_lib "native/libcomcartwrap.dylib"
  attach_function :process_file, [:pointer, :uint], :void

  def self.process(path)
    data = IO.binread(path)
    process_file(data, data.size)
  end
end
