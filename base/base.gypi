# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'target_defaults': {
    'variables': {
      'base_target': 0,
    },
    'target_conditions': [
      # This part is shared between the targets defined below.
      ['base_target==1', {
        'sources': [
          '../build/build_config.h',
          'third_party/dmg_fp/dmg_fp.h',
          'third_party/dmg_fp/g_fmt.cc',
          'third_party/dmg_fp/dtoa_wrapper.cc',
          'third_party/icu/icu_utf.cc',
          'third_party/icu/icu_utf.h',
          'third_party/nspr/prtime.cc',
          'third_party/nspr/prtime.h',
          'third_party/nspr/prcpucfg_linux.h',
          'third_party/xdg_mime/xdgmime.h',
          'allocator/allocator_extension.cc',
          'allocator/allocator_extension.h',
          'allocator/type_profiler_control.cc',
          'allocator/type_profiler_control.h',
          'android/base_jni_registrar.cc',
          'android/base_jni_registrar.h',
          'android/build_info.cc',
          'android/build_info.h',
          'android/cpu_features.cc',
          'android/scoped_java_ref.cc',
          'android/scoped_java_ref.h',
          'android/jni_android.cc',
          'android/jni_android.h',
          'android/jni_array.cc',
          'android/jni_array.h',
          'android/jni_helper.cc',
          'android/jni_helper.h',
          'android/jni_registrar.cc',
          'android/jni_registrar.h',
          'android/jni_string.cc',
          'android/jni_string.h',
          'android/locale_utils.cc',
          'android/locale_utils.h',
          'android/path_service_android.cc',
          'android/path_service_android.h',
          'android/path_utils.cc',
          'android/path_utils.h',
          'at_exit.cc',
          'at_exit.h',
          'atomic_ref_count.h',
          'atomic_sequence_num.h',
          'atomicops.h',
          'atomicops_internals_gcc.h',
          'atomicops_internals_mac.h',
          'atomicops_internals_tsan.h',
          'atomicops_internals_x86_gcc.cc',
          'atomicops_internals_x86_gcc.h',
          'atomicops_internals_x86_msvc.h',
          'base_export.h',
          'base_paths.cc',
          'base_paths.h',
          'base_paths_android.cc',
          'base_paths_android.h',
          'base_paths_mac.h',
          'base_paths_mac.mm',
          'base_paths_posix.cc',
          'base_paths_posix.h',
          'base_paths_win.cc',
          'base_paths_win.h',
          'base_switches.h',
          'base64.cc',
          'base64.h',
          'basictypes.h',
          'bind.h',
          'bind_helpers.cc',
          'bind_helpers.h',
          'bind_internal.h',
          'bind_internal_functor.h',
          'bind_internal_win.h',
          'bits.h',
          'build_time.cc',
          'build_time.h',
          'callback.h',
          'callback_helpers.h',
          'callback_internal.cc',
          'callback_internal.h',
          'cancelable_callback.h',
          'chromeos/chromeos_version.cc',
          'chromeos/chromeos_version.h',
          'command_line.cc',
          'command_line.h',
          'compiler_specific.h',
          'containers/linked_hash_map.h',
          'containers/linked_list.h',
          'containers/mru_cache.h',
          'containers/small_map.h',
          'containers/stack_container.h',
          'cpu.cc',
          'cpu.h',
          'critical_closure.h',
          'critical_closure_ios.mm',
          'debug/alias.cc',
          'debug/alias.h',
          'debug/debug_on_start_win.cc',
          'debug/debug_on_start_win.h',
          'debug/debugger.cc',
          'debug/debugger.h',
          'debug/debugger_posix.cc',
          'debug/debugger_win.cc',
          # This file depends on files from the 'allocator' target,
          # but this target does not depend on 'allocator' (see
          # allocator.gyp for details).
          'debug/leak_annotations.h',
          'debug/leak_tracker.h',
          'debug/profiler.cc',
          'debug/profiler.h',
          'debug/stack_trace.cc',
          'debug/stack_trace.h',
          'debug/stack_trace_android.cc',
          'debug/stack_trace_ios.mm',
          'debug/stack_trace_posix.cc',
          'debug/stack_trace_win.cc',
          'debug/trace_event.cc',
          'debug/trace_event.h',
          'debug/trace_event_android.cc',
          'debug/trace_event_impl.cc',
          'debug/trace_event_impl.h',
          'debug/trace_event_win.cc',
          'environment.cc',
          'environment.h',
          'file_descriptor_posix.h',
          'file_path.cc',
          'file_path.h',
          'file_util.cc',
          'file_util.h',
          'file_util_android.cc',
          'file_util_linux.cc',
          'file_util_mac.mm',
          'file_util_posix.cc',
          'file_util_win.cc',
          'file_util_proxy.cc',
          'file_util_proxy.h',
          'file_version_info.h',
          'file_version_info_mac.h',
          'file_version_info_mac.mm',
          'file_version_info_win.cc',
          'file_version_info_win.h',
          'files/dir_reader_fallback.h',
          'files/dir_reader_dirent.h',
          'files/dir_reader_linux.h',
          'files/dir_reader_posix.h',
          'files/file_path_watcher.cc',
          'files/file_path_watcher.h',
          'files/file_path_watcher_kqueue.cc',
          'files/file_path_watcher_linux.cc',
          'files/file_path_watcher_stub.cc',
          'files/file_path_watcher_win.cc',
          'files/important_file_writer.h',
          'files/important_file_writer.cc',
          'files/scoped_temp_dir.cc',
          'files/scoped_temp_dir.h',
          'float_util.h',
          'format_macros.h',
          'gtest_prod_util.h',
          'guid.cc',
          'guid.h',
          'guid_posix.cc',
          'guid_win.cc',
          'hash.cc',
          'hash.h',
          'hash_tables.h',
          'hi_res_timer_manager_posix.cc',
          'hi_res_timer_manager_win.cc',
          'hi_res_timer_manager.h',
          'id_map.h',
          'ios/device_util.h',
          'ios/device_util.mm',
          'ios/ios_util.h',
          'ios/ios_util.mm',
          'ios/scoped_critical_action.h',
          'ios/scoped_critical_action.mm',
          'json/json_file_value_serializer.cc',
          'json/json_file_value_serializer.h',
          'json/json_parser.cc',
          'json/json_parser.h',
          'json/json_reader.cc',
          'json/json_reader.h',
          'json/json_string_value_serializer.cc',
          'json/json_string_value_serializer.h',
          'json/json_value_converter.h',
          'json/json_writer.cc',
          'json/json_writer.h',
          'json/string_escape.cc',
          'json/string_escape.h',
          'lazy_instance.cc',
          'lazy_instance.h',
          'location.cc',
          'location.h',
          'logging.cc',
          'logging.h',
          'logging_win.cc',
          'logging_win.h',
          'mac/authorization_util.h',
          'mac/authorization_util.mm',
          'mac/bind_objc_block.h',
          'mac/bind_objc_block.mm',
          'mac/bundle_locations.h',
          'mac/bundle_locations.mm',
          'mac/cocoa_protocols.h',
          'mac/crash_logging.h',
          'mac/crash_logging.mm',
          'mac/foundation_util.h',
          'mac/foundation_util.mm',
          'mac/launchd.cc',
          'mac/launchd.h',
          'mac/libdispatch_task_runner.cc',
          'mac/libdispatch_task_runner.h',
          'mac/mac_logging.h',
          'mac/mac_logging.cc',
          'mac/mac_util.h',
          'mac/mac_util.mm',
          'mac/objc_property_releaser.h',
          'mac/objc_property_releaser.mm',
          'mac/os_crash_dumps.cc',
          'mac/os_crash_dumps.h',
          'mac/scoped_aedesc.h',
          'mac/scoped_authorizationref.h',
          'mac/scoped_cftyperef.h',
          'mac/scoped_ioobject.h',
          'mac/scoped_launch_data.h',
          'mac/scoped_mach_port.cc',
          'mac/scoped_mach_port.h',
          'mac/scoped_nsautorelease_pool.h',
          'mac/scoped_nsautorelease_pool.mm',
          'mac/scoped_nsexception_enabler.h',
          'mac/scoped_nsexception_enabler.mm',
          'mac/scoped_sending_event.h',
          'mac/scoped_sending_event.mm',
          'mach_ipc_mac.h',
          'mach_ipc_mac.mm',
          'memory/aligned_memory.cc',
          'memory/aligned_memory.h',
          'memory/linked_ptr.h',
          'memory/manual_constructor.h',
          'memory/raw_scoped_refptr_mismatch_checker.h',
          'memory/ref_counted.cc',
          'memory/ref_counted.h',
          'memory/ref_counted_memory.cc',
          'memory/ref_counted_memory.h',
          'memory/scoped_handle.h',
          'memory/scoped_nsobject.h',
          'memory/scoped_open_process.h',
          'memory/scoped_policy.h',
          'memory/scoped_ptr.h',
          'memory/scoped_vector.h',
          'memory/singleton.cc',
          'memory/singleton.h',
          'memory/weak_ptr.cc',
          'memory/weak_ptr.h',
          'message_loop.cc',
          'message_loop.h',
          'message_loop_proxy.cc',
          'message_loop_proxy.h',
          'message_loop_proxy_impl.cc',
          'message_loop_proxy_impl.h',
          'message_pump.cc',
          'message_pump.h',
          'message_pump_android.cc',
          'message_pump_android.h',
          'message_pump_default.cc',
          'message_pump_default.h',
          'message_pump_win.cc',
          'message_pump_win.h',
          'metrics/sample_map.cc',
          'metrics/sample_map.h',
          'metrics/sample_vector.cc',
          'metrics/sample_vector.h',
          'metrics/bucket_ranges.cc',
          'metrics/bucket_ranges.h',
          'metrics/histogram.cc',
          'metrics/histogram.h',
          'metrics/histogram_base.cc',
          'metrics/histogram_base.h',
          'metrics/histogram_flattener.h',
          'metrics/histogram_samples.cc',
          'metrics/histogram_samples.h',
          'metrics/histogram_snapshot_manager.cc',
          'metrics/histogram_snapshot_manager.h',
          'metrics/sparse_histogram.cc',
          'metrics/sparse_histogram.h',
          'metrics/statistics_recorder.cc',
          'metrics/statistics_recorder.h',
          'metrics/stats_counters.cc',
          'metrics/stats_counters.h',
          'metrics/stats_table.cc',
          'metrics/stats_table.h',
          'move.h',
          'native_library.h',
          'native_library_mac.mm',
          'native_library_posix.cc',
          'native_library_win.cc',
          'observer_list.h',
          'observer_list_threadsafe.h',
          'os_compat_android.cc',
          'os_compat_android.h',
          'os_compat_nacl.cc',
          'os_compat_nacl.h',
          'path_service.cc',
          'path_service.h',
          'pending_task.cc',
          'pending_task.h',
          'pickle.cc',
          'pickle.h',
          'platform_file.cc',
          'platform_file.h',
          'platform_file_posix.cc',
          'platform_file_win.cc',
          'port.h',
          'posix/eintr_wrapper.h',
          'posix/global_descriptors.cc',
          'posix/global_descriptors.h',
          'posix/unix_domain_socket.cc',
          'posix/unix_domain_socket.h',
          'process.h',
          'process_info.h',
          'process_info_mac.cc',
          'process_info_win.cc',
          'process_linux.cc',
          'process_posix.cc',
          'process_util.cc',
          'process_util.h',
          'process_util_freebsd.cc',
          'process_util_ios.mm',
          'process_util_linux.cc',
          'process_util_mac.mm',
          'process_util_openbsd.cc',
          'process_util_posix.cc',
          'process_util_win.cc',
          'process_win.cc',
          'profiler/scoped_profile.cc',
          'profiler/scoped_profile.h',
          'profiler/alternate_timer.cc',
          'profiler/alternate_timer.h',
          'profiler/tracked_time.cc',
          'profiler/tracked_time.h',
          'rand_util.cc',
          'rand_util.h',
          'rand_util_nacl.cc',
          'rand_util_posix.cc',
          'rand_util_win.cc',
          'run_loop.cc',
          'run_loop.h',
          'safe_strerror_posix.cc',
          'safe_strerror_posix.h',
          'scoped_native_library.cc',
          'scoped_native_library.h',
          'sequenced_task_runner.cc',
          'sequenced_task_runner.h',
          'sequenced_task_runner_helpers.h',
          'sha1.h',
          'sha1_portable.cc',
          'sha1_win.cc',
          'shared_memory.h',
          'shared_memory_android.cc',
          'shared_memory_nacl.cc',
          'shared_memory_posix.cc',
          'shared_memory_win.cc',
          'single_thread_task_runner.h',
          'stl_util.h',
          'string_number_conversions.cc',
          'string_number_conversions.h',
          'string_piece.cc',
          'string_piece.h',
          'string_split.cc',
          'string_split.h',
          'string_tokenizer.h',
          'string_util.cc',
          'string_util.h',
          'string_util_posix.h',
          'string_util_win.h',
          'string16.cc',
          'string16.h',
          'stringize_macros.h',
          'stringprintf.cc',
          'stringprintf.h',
          'supports_user_data.cc',
          'supports_user_data.h',
          'synchronization/cancellation_flag.cc',
          'synchronization/cancellation_flag.h',
          'synchronization/condition_variable.h',
          'synchronization/condition_variable_posix.cc',
          'synchronization/condition_variable_win.cc',
          'synchronization/lock.cc',
          'synchronization/lock.h',
          'synchronization/lock_impl.h',
          'synchronization/lock_impl_posix.cc',
          'synchronization/lock_impl_win.cc',
          'synchronization/waitable_event.h',
          'synchronization/waitable_event_posix.cc',
          'synchronization/waitable_event_watcher.h',
          'synchronization/waitable_event_watcher_posix.cc',
          'synchronization/waitable_event_watcher_win.cc',
          'synchronization/waitable_event_win.cc',
          'system_monitor/system_monitor.cc',
          'system_monitor/system_monitor.h',
          'system_monitor/system_monitor_android.cc',
          'system_monitor/system_monitor_android.h',
          'system_monitor/system_monitor_ios.mm',
          'system_monitor/system_monitor_mac.mm',
          'system_monitor/system_monitor_posix.cc',
          'system_monitor/system_monitor_win.cc',
          'sys_byteorder.h',
          'sys_info.cc',
          'sys_info.h',
          'sys_info_android.cc',
          'sys_info_chromeos.cc',
          'sys_info_freebsd.cc',
          'sys_info_ios.mm',
          'sys_info_linux.cc',
          'sys_info_mac.cc',
          'sys_info_openbsd.cc',
          'sys_info_posix.cc',
          'sys_info_win.cc',
          'sys_string_conversions.h',
          'sys_string_conversions_mac.mm',
          'sys_string_conversions_posix.cc',
          'sys_string_conversions_win.cc',
          'task_runner.cc',
          'task_runner.h',
          'task_runner_util.h',
          'template_util.h',
          'thread_task_runner_handle.cc',
          'thread_task_runner_handle.h',
          'threading/non_thread_safe.h',
          'threading/non_thread_safe_impl.cc',
          'threading/non_thread_safe_impl.h',
          'threading/platform_thread.h',
          'threading/platform_thread_mac.mm',
          'threading/platform_thread_posix.cc',
          'threading/platform_thread_win.cc',
          'threading/post_task_and_reply_impl.cc',
          'threading/post_task_and_reply_impl.h',
          'threading/sequenced_worker_pool.cc',
          'threading/sequenced_worker_pool.h',
          'threading/simple_thread.cc',
          'threading/simple_thread.h',
          'threading/thread.cc',
          'threading/thread.h',
          'threading/thread_checker.h',
          'threading/thread_checker_impl.cc',
          'threading/thread_checker_impl.h',
          'threading/thread_collision_warner.cc',
          'threading/thread_collision_warner.h',
          'threading/thread_local.h',
          'threading/thread_local_posix.cc',
          'threading/thread_local_storage.h',
          'threading/thread_local_storage_posix.cc',
          'threading/thread_local_storage_win.cc',
          'threading/thread_local_win.cc',
          'threading/thread_restrictions.h',
          'threading/thread_restrictions.cc',
          'threading/watchdog.cc',
          'threading/watchdog.h',
          'threading/worker_pool.h',
          'threading/worker_pool.cc',
          'threading/worker_pool_posix.cc',
          'threading/worker_pool_posix.h',
          'threading/worker_pool_win.cc',
          'time.cc',
          'time.h',
          'time_mac.cc',
          'time_posix.cc',
          'time_win.cc',
          'timer.cc',
          'timer.h',
          'tracked_objects.cc',
          'tracked_objects.h',
          'tracking_info.cc',
          'tracking_info.h',
          'tuple.h',
          'utf_offset_string_conversions.cc',
          'utf_offset_string_conversions.h',
          'utf_string_conversion_utils.cc',
          'utf_string_conversion_utils.h',
          'utf_string_conversions.cc',
          'utf_string_conversions.h',
          'values.cc',
          'values.h',
          'value_conversions.cc',
          'value_conversions.h',
          'version.cc',
          'version.h',
          'vlog.cc',
          'vlog.h',
          'nix/mime_util_xdg.cc',
          'nix/mime_util_xdg.h',
          'nix/xdg_util.cc',
          'nix/xdg_util.h',
          'win/enum_variant.h',
          'win/enum_variant.cc',
          'win/event_trace_consumer.h',
          'win/event_trace_controller.cc',
          'win/event_trace_controller.h',
          'win/event_trace_provider.cc',
          'win/event_trace_provider.h',
          'win/i18n.cc',
          'win/i18n.h',
          'win/iat_patch_function.cc',
          'win/iat_patch_function.h',
          'win/iunknown_impl.h',
          'win/iunknown_impl.cc',
          'win/metro.cc',
          'win/metro.h',
          'win/object_watcher.cc',
          'win/object_watcher.h',
          'win/registry.cc',
          'win/registry.h',
          'win/resource_util.cc',
          'win/resource_util.h',
          'win/sampling_profiler.cc',
          'win/sampling_profiler.h',
          'win/scoped_bstr.cc',
          'win/scoped_bstr.h',
          'win/scoped_co_mem.h',
          'win/scoped_com_initializer.h',
          'win/scoped_comptr.h',
          'win/scoped_gdi_object.h',
          'win/scoped_handle.cc',
          'win/scoped_handle.h',
          'win/scoped_hdc.h',
          'win/scoped_hglobal.h',
          'win/scoped_process_information.cc',
          'win/scoped_process_information.h',
          'win/scoped_select_object.h',
          'win/shortcut.cc',
          'win/shortcut.h',
          'win/startup_information.cc',
          'win/startup_information.h',
          'win/scoped_variant.cc',
          'win/scoped_variant.h',
          'win/text_services_message_filter.cc',
          'win/text_services_message_filter.h',
          'win/windows_version.cc',
          'win/windows_version.h',
          'win/win_util.cc',
          'win/win_util.h',
          'win/wrapped_window_proc.cc',
          'win/wrapped_window_proc.h',
        ],
        'defines': [
          'BASE_IMPLEMENTATION',
        ],
        'include_dirs': [
          '..',
        ],
        'msvs_disabled_warnings': [
          4018,
        ],
        'conditions': [
          ['OS=="lb_shell"', {
            'sources': [
              'base_paths_shell.cc',
              'circular_buffer_shell.h',
              'circular_buffer_shell.cc',
              'message_pump_shell.cc',
              'message_pump_shell.h',
              'native_library_shell.cc',  # Stub implementation
              'object_watcher_shell.cc',
              'object_watcher_shell.h',
              'optional.cc',
              'optional.h',
              'optional_internal.h',
              'shared_memory_shell.cc',  # Stub implementation
              'state_machine_shell.h',
              'state_machine_shell.cc',
              'synchronization/condition_variable_shell.cc',
              'synchronization/lock_impl_shell.cc',
              'synchronization/waitable_event_shell.cc',
              'threading/thread_checker_impl_atomic.cc',
              '<!@(find <(lbshell_root)/src/platform/<(target_arch)/chromium/base -type f)',
            ],
            'sources!': [
               'threading/thread_checker_impl.cc',
            ],
            'sources/': [
              ['include', 'sys_string_conversions_linux.cc'],
            ],
          }],
          [ 'OS=="lb_shell" and target_arch!="linux" and target_arch!="android"', {
            'sources!': [
              'string16.cc',  # wchar_t is 2-bytes wide, string16 == wstring here.
            ],
          }],
          [ 'OS=="lb_shell" and target_arch=="android"', {
            'sources/' : [
              ['exclude', 'message_pump_shell.cc'],
              ['exclude', 'message_pump_shell.h'],
              ['exclude', 'native_library_shell.cc'],
              ['exclude', 'process_util.cc'],
              ['exclude', '<(lbshell_root)/src/object_watcher_shell.cc'],
              ['exclude', '<(lbshell_root)/src/object_watcher_shell.h'],
              ['include', 'message_pump_libevent.cc'],
              ['include', 'message_pump_libevent.h'],
              ['include', 'native_library_posix.cc'],
            ],
          }],
          # For Starboard, we are going to build this back up as necessary.
          ['OS=="starboard"', {
            'sources': [
              'base_paths_starboard.cc',
              'circular_buffer_shell.cc',
              'circular_buffer_shell.h',
              'debug/debugger_starboard.cc',
              'debug/stack_trace_starboard.cc',
              'file_util_starboard.cc',
              'guid_starboard.cc',
              'message_pump_io_starboard.cc',
              'message_pump_io_starboard.h',
              'message_pump_ui_starboard.cc',
              'message_pump_ui_starboard.h',
              'optional.cc',
              'optional.h',
              'optional_internal.h',
              'platform_file_starboard.cc',
              'process_starboard.cc',
              'process_util_starboard.cc',
              'rand_util_starboard.cc',
              'state_machine_shell.cc',
              'state_machine_shell.h',
              'synchronization/condition_variable_starboard.cc',
              'synchronization/lock_impl_starboard.cc',
              'synchronization/waitable_event_starboard.cc',
              'sys_info_starboard.cc',
              'sys_string_conversions_starboard.cc',
              'system_monitor/system_monitor_starboard.cc',
              'threading/platform_thread_starboard.cc',
              'threading/thread_checker_impl_atomic.cc',
              'threading/thread_local_starboard.cc',
              'threading/thread_local_storage_starboard.cc',
              'threading/worker_pool_starboard.cc',
              'time_starboard.cc',
            ],
            'sources!': [
              # Uses file_util::ReplaceFile, which isn't implemented in
              # Starboard, and isn't otherwise used in Cobalt.
              'files/important_file_writer.cc',
              'files/important_file_writer.h',

              # All the common functions have been removed for Starboard, so we
              # don't even want to compile this.
              'process_util.cc',

              # Tricky to support cross-platform, and not used by Cobalt.
              'scoped_native_library.cc',
              'scoped_native_library.h',

              # We use thread_checker_impl_atomic.cc instead.
              'threading/thread_checker_impl.cc',
            ],
            'conditions': [
              ['target_os!="linux" and target_os!="android"', {
                'sources!': [
                  # Since wchar_t is 2-bytes wide, string16 == wstring here.
                  'string16.cc',
                ],
              }],
            ],
          }],  # OS == "starboard"
          [ 'OS=="lb_shell" or OS=="starboard"', {
            'sources!': [
              'environment.cc',
              'file_descriptor_shuffle.cc',
              'files/file_path_watcher.cc',
              'files/file_path_watcher_kqueue.cc',
              'files/file_path_watcher_stub.cc',
              'message_pump_libevent.cc',
              'message_pump_libevent.h',
              'metrics/stats_table.cc',
              'metrics/stats_table.h',
            ],
          }],  # OS == "lb_shell" or OS == "starboard"
        ],
        'target_conditions': [
          ['<(use_glib)==0 or >(nacl_untrusted_build)==1', {
              'sources/': [
                ['exclude', '^nix/'],
              ],
              'sources!': [
                'atomicops_internals_x86_gcc.cc',
                'message_pump_glib.cc',
                'message_pump_aurax11.cc',
              ],
          }],
          ['<(toolkit_uses_gtk)==0 or >(nacl_untrusted_build)==1', {
            'sources!': ['message_pump_gtk.cc'],
          }],
          ['(OS != "linux" and <(os_bsd) != 1 and OS != "android") or >(nacl_untrusted_build)==1', {
              'sources!': [
                # Not automatically excluded by the *linux.cc rules.
                'linux_util.cc',
              ],
            },
          ],
          ['>(nacl_untrusted_build)==1', {
            'sources!': [
               'allocator/type_profiler_control.cc',
               'allocator/type_profiler_control.h',
               'base_paths.cc',
               'command_line.cc',
               'cpu.cc',
               'debug/stack_trace_posix.cc',
               'file_util.cc',
               'file_util_posix.cc',
               'file_util_proxy.cc',
               'files/file_path_watcher_kqueue.cc',
               'native_library_posix.cc',
               'path_service.cc',
               'platform_file_posix.cc',
               'posix/unix_domain_socket.cc',
               'process_posix.cc',
               'process_util.cc',
               'process_util_posix.cc',
               'rand_util_posix.cc',
               'scoped_native_library.cc',
               'files/scoped_temp_dir.cc',
               'shared_memory_posix.cc',
               'sys_info_posix.cc',
               'threading/sequenced_worker_pool.cc',
               'third_party/dynamic_annotations/dynamic_annotations.c',
            ],
            # Metrics won't work in the NaCl sandbox.
            'sources/': [ ['exclude', '^metrics/'] ],
          }],
          ['OS == "android" and >(nacl_untrusted_build)==0', {
            'sources!': [
              'base_paths_posix.cc',
              'files/file_path_watcher_kqueue.cc',
              'files/file_path_watcher_stub.cc',
              'system_monitor/system_monitor_posix.cc',
            ],
            'sources/': [
              ['include', '^files/file_path_watcher_linux\\.cc$'],
              ['include', '^process_util_linux\\.cc$'],
              ['include', '^sys_info_linux\\.cc$'],
              ['include', '^sys_string_conversions_posix\\.cc$'],
              ['include', '^worker_pool_linux\\.cc$'],
            ],
          }],
          ['OS == "ios"', {
            'sources/': [
              # Pull in specific Mac files for iOS (which have been filtered out
              # by file name rules).
              ['include', '^atomicops_internals_mac\\.'],
              ['include', '^base_paths_mac\\.'],
              ['include', '^file_util_mac\\.'],
              ['include', '^file_version_info_mac\\.'],
              ['include', '^mac/bind_objc_block\\.'],
              ['include', '^mac/bundle_locations\\.'],
              ['include', '^mac/foundation_util\\.'],
              ['include', '^mac/mac_logging\\.'],
              ['include', '^mac/objc_property_releaser\\.'],
              ['include', '^mac/scoped_mach_port\\.'],
              ['include', '^mac/scoped_nsautorelease_pool\\.'],
              ['include', '^message_pump_mac\\.'],
              ['include', '^threading/platform_thread_mac\\.'],
              ['include', '^sys_string_conversions_mac\\.'],
              ['include', '^time_mac\\.'],
              ['include', '^worker_pool_mac\\.'],
              # Exclude all process_util except the minimal implementation
              # needed on iOS (mostly for unit tests).
              ['exclude', '^process_util'],
              ['include', '^process_util_ios\\.mm$'],
            ],
            'sources!': [
              'message_pump_libevent.cc'
            ],
          }],
          ['OS != "mac" or >(nacl_untrusted_build)==1', {
              'sources!': [
                'mac/scoped_aedesc.h'
              ],
          }],
          # For now, just test the *BSD platforms enough to exclude them.
          # Subsequent changes will include them further.
          ['OS != "freebsd" or >(nacl_untrusted_build)==1', {
              'sources/': [ ['exclude', '_freebsd\\.cc$'] ],
            },
          ],
          ['OS != "openbsd" or >(nacl_untrusted_build)==1', {
              'sources/': [ ['exclude', '_openbsd\\.cc$'] ],
            },
          ],
          ['OS != "win" or >(nacl_untrusted_build)==1', {
              'sources/': [ ['exclude', '^win/'] ],
            },
          ],
          ['(OS != "android" or >(nacl_untrusted_build)==1) and (OS != "lb_shell" or "<(target_arch)" != "android")', {
              'sources/': [ ['exclude', '^android/'] ],
            },
          ],
          ['OS == "win" and >(nacl_untrusted_build)==0', {
            'include_dirs': [
              '<(DEPTH)/third_party/wtl/include',
            ],
            'sources!': [
              'event_recorder_stubs.cc',
              'files/file_path_watcher_kqueue.cc',
              'files/file_path_watcher_stub.cc',
              'message_pump_libevent.cc',
              'posix/file_descriptor_shuffle.cc',
              # Not using sha1_win.cc because it may have caused a
              # regression to page cycler moz.
              'sha1_win.cc',
              'string16.cc',
            ],
          },],
          ['OS == "linux" and >(nacl_untrusted_build)==0', {
            'sources!': [
              'files/file_path_watcher_kqueue.cc',
              'files/file_path_watcher_stub.cc',
            ],
          }],
          ['(OS == "mac" or OS == "ios") and >(nacl_untrusted_build)==0', {
            'sources/': [
              ['exclude', '^files/file_path_watcher_stub\\.cc$'],
              ['exclude', '^base_paths_posix\\.cc$'],
              ['exclude', '^native_library_posix\\.cc$'],
              ['exclude', '^sys_string_conversions_posix\\.cc$'],
            ],
          }],
          ['<(os_bsd)==1 and >(nacl_untrusted_build)==0', {
            'sources/': [
              ['exclude', '^files/file_path_watcher_linux\\.cc$'],
              ['exclude', '^files/file_path_watcher_stub\\.cc$'],
              ['exclude', '^file_util_linux\\.cc$'],
              ['exclude', '^process_linux\\.cc$'],
              ['exclude', '^process_util_linux\\.cc$'],
              ['exclude', '^sys_info_linux\\.cc$'],
            ],
          }],
          ['<(chromeos)!=1 or >(nacl_untrusted_build)==1', {
            'sources/': [
              ['exclude', '^chromeos/'],
            ],
          }],
          # Remove all unnecessary files for build_nexe.py to avoid exceeding
          # command-line-string limitation when building NaCl on Windows.
          ['OS == "win" and >(nacl_untrusted_build)==1', {
              'sources/': [ ['exclude', '\\.h$'] ],
          }],
        ],
      }],
    ],
  },
}
