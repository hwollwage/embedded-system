<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     */
    public function up(): void
    {
        Schema::table('gas_readings', function (Blueprint $table) {
            $table->string('device_id');
            $table->boolean('alarm')->default(false);
        });
    }

    /**
     * Reverse the migrations.
     */
    public function down(): void
    {
        Schema::table('gas_readings', function (Blueprint $table) {
            $table->dropColumn([
                'device_id',
                'alarm'
            ]);
        });
    }
};
