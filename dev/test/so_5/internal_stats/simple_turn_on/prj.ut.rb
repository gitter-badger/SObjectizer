require 'mxx_ru/binary_unittest'

path = 'test/so_5/internal_stats/simple_turn_on'

MxxRu::setup_target(
	MxxRu::BinaryUnittestTarget.new(
		"#{path}/prj.ut.rb",
		"#{path}/prj.rb" )
)
