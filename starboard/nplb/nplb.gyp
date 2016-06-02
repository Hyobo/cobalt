# Copyright 2015 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# NPLB is "No Platform Left Behind," the certification test suite for Starboard
# implementations.

{
  'targets': [
    {
      'target_name': 'nplb',
      'type': '<(gtest_target_type)',
      'sources': [
        'atomic_test.cc',
        'audio_sink_create_test.cc',
        'blitter_blit_rect_to_rect_test.cc',
        'blitter_blit_rect_to_rect_tiled_test.cc',
        'blitter_blit_rects_to_rects_test.cc',
        'blitter_create_context_test.cc',
        'blitter_create_default_device_test.cc',
        'blitter_create_pixel_data_test.cc',
        'blitter_create_render_target_surface_test.cc',
        'blitter_create_surface_from_pixel_data_test.cc',
        'blitter_create_swap_chain_from_window_test.cc',
        'blitter_destroy_context_test.cc',
        'blitter_destroy_device_test.cc',
        'blitter_destroy_pixel_data_test.cc',
        'blitter_destroy_surface_test.cc',
        'blitter_destroy_swap_chain_test.cc',
        'blitter_download_surface_pixel_data_as_rgba_test.cc',
        'blitter_fill_rect_test.cc',
        'blitter_flip_swap_chain_test.cc',
        'blitter_flush_context_test.cc',
        'blitter_get_max_contexts_test.cc',
        'blitter_get_pixel_data_pitch_in_bytes_test.cc',
        'blitter_get_pixel_data_pointer_test.cc',
        'blitter_get_render_target_from_surface_test.cc',
        'blitter_get_render_target_from_swap_chain_test.cc',
        'blitter_get_surface_info_test.cc',
        'blitter_helpers.cc',
        'blitter_is_pixel_format_supported_by_pixel_data_test.cc',
        'blitter_is_pixel_format_supported_by_render_target_surface_test.cc',
        'blitter_set_blending_test.cc',
        'blitter_set_modulate_blits_with_color_test.cc',
        'blitter_set_render_target_test.cc',
        'byte_swap_test.cc',
        'character_is_alphanumeric_test.cc',
        'character_is_digit_test.cc',
        'character_is_hex_digit_test.cc',
        'character_is_space_test.cc',
        'character_is_upper_test.cc',
        'character_to_lower_test.cc',
        'character_to_upper_test.cc',
        'condition_variable_broadcast_test.cc',
        'condition_variable_create_test.cc',
        'condition_variable_destroy_test.cc',
        'condition_variable_signal_test.cc',
        'condition_variable_wait_test.cc',
        'condition_variable_wait_timed_test.cc',
        'configuration_test.cc',
        'directory_can_open_test.cc',
        'directory_close_test.cc',
        'directory_create_test.cc',
        'directory_get_next_test.cc',
        'directory_open_test.cc',
        'double_absolute_test.cc',
        'double_exponent_test.cc',
        'double_floor_test.cc',
        'double_is_finite_test.cc',
        'double_is_nan_test.cc',
        'file_can_open_test.cc',
        'file_close_test.cc',
        'file_get_info_test.cc',
        'file_get_path_info_test.cc',
        'file_helpers.cc',
        'file_mode_string_to_flags_test.cc',
        'file_open_test.cc',
        'file_read_test.cc',
        'file_seek_test.cc',
        'file_truncate_test.cc',
        'file_write_test.cc',
        'include_all.c',
        'log_flush_test.cc',
        'log_format_test.cc',
        'log_is_tty_test.cc',
        'log_raw_dump_stack_test.cc',
        'log_raw_test.cc',
        'log_test.cc',
        'main.cc',
        'memory_allocate_aligned_test.cc',
        'memory_allocate_test.cc',
        'memory_compare_test.cc',
        'memory_copy_test.cc',
        'memory_find_byte_test.cc',
        'memory_free_aligned_test.cc',
        'memory_free_test.cc',
        'memory_get_stack_bounds_test.cc',
        'memory_map_test.cc',
        'memory_move_test.cc',
        'memory_reallocate_test.cc',
        'memory_set_test.cc',
        'mutex_acquire_test.cc',
        'mutex_acquire_try_test.cc',
        'mutex_create_test.cc',
        'mutex_destroy_test.cc',
        'once_test.cc',
        'player_create_test.cc',
        'random_helpers.cc',
        'socket_accept_test.cc',
        'socket_bind_test.cc',
        'socket_clear_last_error_test.cc',
        'socket_connect_test.cc',
        'socket_create_test.cc',
        'socket_destroy_test.cc',
        'socket_get_last_error_test.cc',
        'socket_get_local_address_test.cc',
        'socket_get_local_interface_address_test.cc',
        'socket_helpers.cc',
        'socket_is_connected_and_idle_test.cc',
        'socket_is_connected_test.cc',
        'socket_join_multicast_group_test.cc',
        'socket_listen_test.cc',
        'socket_receive_from_test.cc',
        'socket_resolve_test.cc',
        'socket_send_to_test.cc',
        'socket_set_options_test.cc',
        'socket_waiter_add_test.cc',
        'socket_waiter_create_test.cc',
        'socket_waiter_destroy_test.cc',
        'socket_waiter_remove_test.cc',
        'socket_waiter_wait_test.cc',
        'socket_waiter_wait_timed_test.cc',
        'socket_waiter_wake_up_test.cc',
        'storage_close_record_test.cc',
        'storage_delete_record_test.cc',
        'storage_get_record_size_test.cc',
        'storage_open_record_test.cc',
        'storage_read_record_test.cc',
        'storage_write_record_test.cc',
        'string_compare_all_test.cc',
        'string_compare_no_case_n_test.cc',
        'string_compare_no_case_test.cc',
        'string_compare_test.cc',
        'string_compare_wide_test.cc',
        'string_concat_test.cc',
        'string_concat_wide_test.cc',
        'string_copy_test.cc',
        'string_copy_wide_test.cc',
        'string_duplicate_test.cc',
        'string_find_character_test.cc',
        'string_find_last_character_test.cc',
        'string_find_string_test.cc',
        'string_format_test.cc',
        'string_format_wide_test.cc',
        'string_parse_signed_integer_test.cc',
        'string_parse_uint64_test.cc',
        'string_parse_unsigned_integer_test.cc',
        'string_scan_test.cc',
        'system_binary_search_test.cc',
        'system_clear_last_error_test.cc',
        'system_get_error_string_test.cc',
        'system_get_last_error_test.cc',
        'system_get_locale_id_test.cc',
        'system_get_number_of_processors_test.cc',
        'system_get_path_test.cc',
        'system_get_property_test.cc',
        'system_get_random_data_test.cc',
        'system_get_random_uint64_test.cc',
        'system_get_stack_test.cc',
        'system_get_total_memory_test.cc',
        'system_has_capability_test.cc',
        'system_is_debugger_attached_test.cc',
        'system_sort_test.cc',
        'system_symbolize_test.cc',
        'thread_create_test.cc',
        'thread_detach_test.cc',
        'thread_get_current_test.cc',
        'thread_get_id_test.cc',
        'thread_get_name_test.cc',
        'thread_helpers.cc',
        'thread_is_equal_test.cc',
        'thread_join_test.cc',
        'thread_local_value_test.cc',
        'thread_set_name_test.cc',
        'thread_sleep_test.cc',
        'thread_yield_test.cc',
        'time_explode_test.cc',
        'time_get_monotonic_now_test.cc',
        'time_get_now_test.cc',
        'time_implode_test.cc',
        'time_narrow_test.cc',
        'time_zone_get_current_test.cc',
        'time_zone_get_dst_name_test.cc',
        'time_zone_get_name_test.cc',
        'user_get_current_test.cc',
        'user_get_property_test.cc',
        'user_get_signed_in_test.cc',
        'window_create_test.cc',
        'window_destroy_test.cc',
        'window_get_platform_handle_test.cc',
        'window_get_size_test.cc',
      ],
      'dependencies': [
        '<(DEPTH)/testing/gmock.gyp:gmock',
        '<(DEPTH)/testing/gtest.gyp:gtest',
        '<(DEPTH)/starboard/starboard.gyp:starboard',
      ],
    },
  ],
}
